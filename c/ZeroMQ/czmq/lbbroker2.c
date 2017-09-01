// 2017-09-01T10:34+08:00
// Rewrite the Load-balancing broker example in:
// https://github.com/booksbyus/zguide/blob/master/examples/C/lbbroker2.c
// with CZMQ 4.x API.

#include <czmq.h>

#include <pthread.h>


#define NBR_CLIENTS 10
#define NBR_WORKERS 3

#define WORKER_READY "READY" // Signals worker is ready
#define YOU_ARE_FIRED "Fired!"



// Based on those code in zframe_print
static void
zframe_dump(zframe_t *frame, const char *prefix, const char *suffix)
{
	assert(frame);
	assert(zframe_is(frame));

	byte *data = zframe_data(frame);
	size_t size = zframe_size(frame);

	//  Probe data to check if it looks like unprintable binary
	int is_bin = 0;
	uint char_nbr;
	for (char_nbr = 0; char_nbr < size; char_nbr++)
		if (data[char_nbr] < 9 || data[char_nbr] > 127)
			is_bin = 1;

	char buffer[256] = "";
	size_t max_size = is_bin ? 35 : 70;
	const char *ellipsis = "";
	if (size > max_size) {
		size = max_size;
		ellipsis = "...";
	}
	for (char_nbr = 0; char_nbr < size; char_nbr++) {
		if (is_bin)
			sprintf(buffer + strlen(buffer), "%02X", (unsigned char)data[char_nbr]);
		else
			sprintf(buffer + strlen(buffer), "%c", data[char_nbr]);
	}
	strcat(buffer, ellipsis);

	printf("%s%s%s", prefix ? prefix : "", buffer, suffix ? suffix : "");
}


// Basic request-reply client using REQ socket
//
static void *
client_task(void *args)
{
    zsock_t *client = zsock_new(ZMQ_REQ);

#if (defined (WIN32))
    zsock_connect(client, "tcp://localhost:5672");
#else
    zsock_connect(client, "ipc://frontend.ipc");
#endif

	zstr_send(client, "HELLO");
	char *reply = zstr_recv(client);
	if (reply) {
		printf("Client: %s\n", reply);
		free(reply);
	}

    zsock_destroy(&client);

    return NULL;
}


// Worker using REQ socket to do load-balancing
//
static void *
worker_task(void *args)
{
    zsock_t *worker = zsock_new(ZMQ_REQ);

#if (defined (WIN32))
    zsock_connect(worker, "tcp://localhost:5673"); // backend
#else
    zsock_connect(worker, "ipc://backend.ipc");
#endif

    // Tell broker we're ready for work
    zframe_t *frame = zframe_new(WORKER_READY, strlen(WORKER_READY));
    zframe_send(&frame, worker, 0);

    // Process messages as they arrive
    while (true) {
        zmsg_t *msg = zmsg_recv(worker);
        if (!msg)
            break; // Interrupted

        if (zmsg_size(msg) == 3) {
            // Boss push me to work!
            zframe_t *request = zmsg_last(msg);
            assert(request);

            zframe_dump(request, "Worker: ", "\n");

            zframe_reset(request, "OK", 2);
            zmsg_send(&msg, worker);
        } else {
            // I am fired!
            assert(zmsg_size(msg) == 1);
            assert(zframe_streq(zmsg_first(msg), YOU_ARE_FIRED));
            zmsg_destroy(&msg);
        }
    }

    zsock_destroy(&worker);

    return NULL;
}


// .split main task
// Now we come to the main task. This has the identical functionality to
// the previous {{lbbroker}} broker example, but uses CZMQ to start child
// threads, to hold the list of workers, and to read and send messages:

int main(void)
{
    int rc = 0;

    zsock_t *frontend = zsock_new(ZMQ_ROUTER);
    zsock_t *backend = zsock_new(ZMQ_ROUTER);

    assert(frontend);
    assert(backend);
    assert(streq(zsock_type_str(frontend), "ROUTER"));
    assert(streq(zsock_type_str(backend), "ROUTER"));

#if (defined (WIN32))
	rc = zsock_bind(frontend, "tcp://*:5672");
    assert(rc == 5672);
	rc = zsock_bind(backend, "tcp://*:5673");
    assert(rc == 5673);
#else
    (void)rc;
    zsock_bind(frontend, "ipc://frontend.ipc");
    zsock_bind(backend, "ipc://backend.ipc");
#endif


    int client_nbr;
    for (client_nbr = 0; client_nbr < NBR_CLIENTS; client_nbr++) {
        pthread_t client;
        pthread_create(&client, NULL, client_task, (void *)(intptr_t)client_nbr);
        //zthread_new(client_task, NULL);
    }

    int worker_nbr;
    for (worker_nbr = 0; worker_nbr < NBR_WORKERS; worker_nbr++) {
        pthread_t worker;
        pthread_create(&worker, NULL, worker_task, (void *)(intptr_t)worker_nbr);
        //zthread_new(worker_task, NULL);
    }

    // Queue of available workers
    zlist_t *workers_list = zlist_new();
    zlist_t *workers_at_rest = zlist_new();

    zpoller_t *backend_poller = zpoller_new(backend, NULL);
    zpoller_t *all_poller = zpoller_new(backend, frontend, NULL);

    // .split main load-balancer loop
    // Here is the main loop for the load balancer. It works the same way
    // as the previous example, but is a lot shorter because CZMQ gives
    // us an API that does more with fewer calls:
    while (true) {
        // Poll frontend only if we have available workers
        zsock_t *reader = zlist_size(workers_at_rest) ? (zsock_t *)zpoller_wait(all_poller, -1) 
            : (zsock_t *)zpoller_wait(backend_poller, -1);

        // Handle worker activity on backend
        if (reader == backend) {
            // Use worker identity for load-balancing
            zmsg_t *msg = zmsg_recv(backend);
            if (!msg)
                break; // Interrupted

			zframe_t *identity = zmsg_pop(msg);

			zframe_t *delimiter = zmsg_first(msg);
			if (delimiter != NULL && zframe_size(delimiter) == 0) {
				delimiter = zmsg_pop(msg);
				zframe_destroy(&delimiter);
			}

            zlist_append(workers_at_rest, identity);

            // Forward message to client if it's not a READY
            zframe_t *frame = zmsg_first(msg);
            if (zframe_streq(frame, WORKER_READY)) {
                zlist_append(workers_list, zframe_dup(identity));
                zmsg_destroy(&msg);
            } else {
                zmsg_send(&msg, frontend);
                if (--client_nbr == 0)
                    break;
            }
        }

        if (reader == frontend) {
            // Get client request, route to first available worker
            zmsg_t *msg = zmsg_recv(frontend);
            if (msg) {
                assert(zmsg_size(msg) == 3);

                rc = zmsg_pushmem(msg, NULL, 0);
                assert(rc == 0);

                zframe_t *identity = (zframe_t *)zlist_pop(workers_at_rest);
                rc = zmsg_prepend(msg, &identity);
                assert(rc == 0);
                
                assert(zmsg_size(msg) == 5);
                zmsg_send(&msg, backend);
            }
        }
    }

    zpoller_destroy(&backend_poller);
    zpoller_destroy(&all_poller);

    // When we're done, clean up properly
    while (zlist_size(workers_at_rest)) {
        zframe_t *frame = (zframe_t *)zlist_pop(workers_at_rest);
        zframe_destroy(&frame);
    }

    zlist_destroy(&workers_at_rest);

    // Cruelly fire all workers. I am the Boss!
    while (zlist_size(workers_list)) {
        zframe_t *worker_id = (zframe_t *)zlist_pop(workers_list);
        assert(zframe_is(worker_id));
        zframe_send(&worker_id, backend, ZFRAME_MORE);

        zframe_t *delimiter = zframe_new_empty();
        zframe_send(&delimiter, backend, ZFRAME_MORE);

        zframe_t *last_talk = zframe_from(YOU_ARE_FIRED);
        zframe_send(&last_talk, backend, 0);
    }

    zlist_destroy(&workers_list);

    zsock_destroy(&frontend);
    zsock_destroy(&backend);

#ifdef __WINDOWS__
    zsys_shutdown();
#endif

    return 0;
}

// References:
// https://github.com/sappo/czmq_zguide_examples/blob/master/src/lpclient.c
// [czmq#1751](https://github.com/zeromq/czmq/issues/1751)
// [zguide#701](https://github.com/booksbyus/zguide/issues/701)
// [zmsg](http://czmq.zeromq.org/czmq4-0:zmsg)
// [zframe](http://czmq.zeromq.org/manual:zframe)
