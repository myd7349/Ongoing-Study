// 2017-09-14T15:17+08:00
// Rewrite the
// Asynchronous client-to-server (DEALER to ROUTER)
// in zguide with czmq 4.x.
//

#include <czmq.h>

#include <pthread.h>

#define NBR_CLIENTS 3


// This is our client task
// It connects to the server, and then sends a request once per second
// It collects responses as they arrive, and it prints them out. We will
// run serval client tasks in parallel, each with a different random ID.

static void *
client_task(void *args)
{
    zsock_t *client = zsock_new(ZMQ_DEALER);

    // Set identity to make tracing easier
    char identity[10];
#if (defined (WIN32))
    sprintf(identity, "%04X", (int)(intptr_t)args);
#else
    sprintf(identity, "%04X-%04X", randof(0x10000), randof(0x10000));
#endif
    zsock_set_identity(client, identity);
    zsock_connect(client, "tcp://localhost:5570");

    zpoller_t *poller = zpoller_new(client, NULL);

    int request_nbr = 0;

    while (true) {
        if (zsys_interrupted)
            break;

        // Tick once per second, pulling in arriving messages
        int centitick;
        for (centitick = 0; centitick < 100; centitick++) {
            void *res = zpoller_wait(poller, 10 * ZMQ_POLL_MSEC);
            if (res == client) {
                zmsg_t *msg = zmsg_recv(client);
                zframe_print(zmsg_last(msg), identity);
                zmsg_destroy(&msg);
            } else if (res == NULL && zpoller_terminated(poller)) {
                break;
            }
        }

        if (zsys_interrupted)
            break;

        zstr_sendf(client, "request #%d", ++request_nbr);

        if (zsys_interrupted)
            break;
    }

    zpoller_destroy(&poller);

    zsock_destroy(&client);

    printf("client_task\n");

    return NULL;
}


// .split worker task
// Each worker task works on one request at a time and sends a random number
// of replies back, with random delays between replies:

static void *
server_worker(void *args)
{
    zsock_t *worker = zsock_new(ZMQ_DEALER);
    int rc = zsock_connect(worker, "inproc://backend");
    assert(rc == 0);

    while (true) {
        // The DEALER socket gives us the reply envelope and message
        zmsg_t *msg = zmsg_recv(worker);
        if (!msg)
            break;

        zframe_t *identity = zmsg_pop(msg);
        zframe_t *content = zmsg_pop(msg);
        assert(content);
        zmsg_destroy(&msg);

        // Send 0..4 replies back
        int reply, replies = randof(5);
        for (reply = 0; reply < replies; reply++) {
            // Sleep for some fraction of a second
            zclock_sleep(randof(1000) + 1);
            if (zframe_send(&identity, worker, ZFRAME_REUSE + ZFRAME_MORE) == -1 ||
                zframe_send(&content, worker, ZFRAME_REUSE) == -1) {
                break;
            }
        }
        zframe_destroy(&identity);
        zframe_destroy(&content);

        if (zsys_interrupted)
            break;
    }

    zsock_destroy(&worker);

    printf("server_worker\n");

    return NULL;
}


// .split server task
// This is our server task
// It uses the multithreaded server model to deal requests out to a pool
// of workers and route replies back to clients. One worker can handle
// one request at a time but one client can talk to multiple workers at once.

void *server_task(void *args)
{
	// Frontend socket talks to clients over TCP
	void *ctx = args;

	void *frontend = zmq_socket(ctx, ZMQ_ROUTER);
    assert(frontend);
	int rc = zmq_bind(frontend, "tcp://*:5570");
    assert(rc == 0);

	// Backend socket talks to workers over inproc
	void *backend = zmq_socket(ctx, ZMQ_DEALER);
    assert(backend);
	zmq_bind(backend, "inproc://backend");

	// Launch pool of worker threads, precise number is not critical
	int thread_nbr;
    for (thread_nbr = 0; thread_nbr < 5; thread_nbr++) {
        pthread_t worker;
        pthread_create(&worker, NULL, server_worker, NULL);
    }

	// Connect backend to frontend via a proxy
	zmq_proxy(frontend, backend, NULL);

    zmq_close(frontend);
    zmq_close(backend);

    printf("server_task\n");

	return NULL;
}

// The main thread simply starts several clients and a server, and then
// waits for the server to finish.

int main(void)
{
    void *ctx = zsys_init();

    //zsys_set_logstream(stdout);

	srandom((unsigned int)time(NULL));

	int client_nbr;
	for (client_nbr = 0; client_nbr < NBR_CLIENTS; client_nbr++) {
        pthread_t client;
        pthread_create(&client, NULL, client_task, (void *)(intptr_t)client_nbr);
	}

    pthread_t server;
    pthread_create(&server, NULL, server_task, ctx);

	zclock_sleep(500 * 10); // Run for 5 seconds then quit

#ifdef __WINDOWS__
    zsys_shutdown();
#endif

	return 0;
}