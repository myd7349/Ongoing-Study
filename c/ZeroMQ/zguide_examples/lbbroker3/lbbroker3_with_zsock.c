// 2017-09-01T16:21+08:00
// Rewrite the Load-balancing broker example in:
// https://github.com/booksbyus/zguide/blob/master/examples/C/lbbroker3.c
// with CZMQ 4.x API.

#include <pthread.h>

#include "czmq_helpers.h"


#define NBR_CLIENTS 10
#define NBR_WORKERS 3
#define WORKER_READY   "READY"      //  Signals worker is ready


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

    // Send request, get reply
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
    zsock_connect(worker, "tcp://localhost:5673");
#else
    zsock_connect(worker, "ipc://backend.ipc");
#endif

    // Tell broker we're ready for work
    zstr_send(worker, WORKER_READY);

    // Process messages as they arrive
    while (1) {
        zmsg_t *msg = zmsg_recv(worker);
        if (!msg)
            break;

        if (zmsg_size(msg) == 3) {
            zframe_dump(zmsg_last(msg), "Worker: ", "\n");
            zframe_reset(zmsg_last(msg), "OK", 2);
            zmsg_send(&msg, worker);
        }
        else {
            assert(false);
        }
    }

    zsock_destroy(&worker);

    return NULL;
}


// .until
// Our load-balancing structure, passed to reactor handlers
typedef struct {
    zsock_t *frontend; // Listen to clients
    zsock_t *backend; // Listen to workers
    zlist_t *workers_at_rest; // List of ready workers
} lbbroker_t;


// .split reactor design
// In the reactor design, each time a message arrives on a socket, the
// reactor passes it to a handler function. We have two handlers; one 
// for the frontend, one for the backend:


// Handle input from client, on frontend
int s_handle_frontend(zloop_t *loop, zsock_t *reader, void *arg)
{
    lbbroker_t *self = (lbbroker_t *)arg;
    zmsg_t *msg = zmsg_recv(self->frontend);
    if (msg) {
        zmsg_wrap(msg, (zframe_t *)zlist_pop(self->workers_at_rest));
        zmsg_send(&msg, self->backend);

        // Cancel reader on frontend if we went from 1 to 0 workers
        if (zlist_size(self->workers_at_rest) == 0)
            zloop_reader_end(loop, self->frontend);
    }

    return 0;
}


// Handle input from worker, on backend
int s_handle_backend(zloop_t *loop, zsock_t *reader, void *arg)
{
    // Use worker identity for load-balancing
    lbbroker_t *self = (lbbroker_t *)arg;
    zmsg_t *msg = zmsg_recv(self->backend);
    if (msg) {
        zframe_t *identity = zmsg_unwrap(msg);
        zlist_append(self->workers_at_rest, identity);

        // Enable reader on frontend if we went from 0 to 1 workers
        if (zlist_size(self->workers_at_rest) == 1) {
            zloop_reader(loop, self->frontend, s_handle_frontend, self);
        }

        // Forward message to client if it's not a READY
        zframe_t *frame = zmsg_first(msg);
        if (zframe_streq(frame, WORKER_READY)) {
            zmsg_destroy(&msg);
        }
        else {
            zmsg_send(&msg, self->frontend);
        }
    }

    return 0;
}


// .split main task
// And the main task now sets up child tasks, then starts its reactor.
// If you press Ctrl-C, the reactor exits and the main task shuts down.
// Because the reactor is a CZMQ class, this example may not translate
// into all languages equally well.

int main(void)
{
    int rc = 0;

    lbbroker_t *self = (lbbroker_t *)zmalloc(sizeof(lbbroker_t));
    self->frontend = zsock_new(ZMQ_ROUTER);
    self->backend = zsock_new(ZMQ_ROUTER);

#if (defined (WIN32))
    zsock_bind(self->frontend, "tcp://*:5672"); // frontend
    zsock_bind(self->backend, "tcp://*:5673"); // backend
#else
    zsock_bind(self->frontend, "ipc://frontend.ipc");
    zsock_bind(self->backend, "ipc://backend.ipc");
#endif

    int client_nbr;
    for (client_nbr = 0; client_nbr < NBR_CLIENTS; client_nbr++) {
        pthread_t client;
        pthread_create(&client, NULL, client_task, NULL);
        //zthread_new(client_task, NULL);
    }

    int worker_nbr;
    for (worker_nbr = 0; worker_nbr < NBR_WORKERS; worker_nbr++) {
        pthread_t worker;
        pthread_create(&worker, NULL, worker_task, NULL);
        //zthread_new(worker_task, NULL);
    }

    // Queue of available workers
    self->workers_at_rest = zlist_new();

    // Prepare reactor and fire it up
    zloop_t *reactor = zloop_new();
    rc = zloop_reader(reactor, self->backend, s_handle_backend, self);
    assert(rc == 0);
    zloop_start(reactor);
    zloop_destroy(&reactor);

    // When we're done, clean up properly
    while (zlist_size(self->workers_at_rest)) {
        zframe_t *frame = (zframe_t *)zlist_pop(self->workers_at_rest);
        zframe_destroy(&frame);
    }
    zlist_destroy(&self->workers_at_rest);

    zsock_destroy(&self->frontend);
    zsock_destroy(&self->backend);

    free(self);

#if defined(__WINDOWS__)
    zsys_shutdown();
#endif

    return 0;
}
