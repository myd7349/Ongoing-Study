// 2015-03-07T11:14+08:00
// Load-balancing broker
// Demonstrates use of the CZMQ API
#include "czmq.h"

#define NBR_CLIENTS 10
#define NBR_WORKERS 3
#define WORKER_READY "\001" // Signals worker is ready

#define DEBUG_POINT() printf("%s: %d\n", __FUNCTION__, __LINE__)

// Basic request-reply client using REQ socket
//
static void *
client_task(void *args)
{
    zctx_t *ctx = zctx_new();
    void *client = zsocket_new(ctx, ZMQ_REQ);

#ifdef WIN32
    zsocket_connect(client, "tcp://localhost:5672"); // frontend
#else
    zsocket_connect(client, "ipc://frontend.ipc");
#endif

    // Send request, get reply
    zstr_send(client, "HELLO");
    char *reply = zstr_recv(client);
    if (reply) {
        printf("Client: %s\n", reply);
        free(reply);
    }

    zsocket_destroy(ctx, client);
    zctx_destroy(&ctx);
    return NULL;
}

// Worker using REQ socket to do load-balancing
//
static void *
worker_task(void *args)
{
    zctx_t *ctx = zctx_new();
    void *worker = zsocket_new(ctx, ZMQ_REQ);

#ifdef WIN32
    zsocket_connect(worker, "tcp://localhost:5673"); // backend
#else
    zsocket_connect(worker, "ipc://backend.ipc");
#endif

    // Tell broker we're ready for work
    zframe_t *frame = zframe_new(WORKER_READY, 1);
    zframe_send(&frame, worker, 0);

    // Process messages as they arrive
    while (1) {
        zmsg_t *msg = zmsg_recv(worker);
        if (!msg)
            break; // Interrupted
        zframe_reset(zmsg_last(msg), "OK", 2);
        zmsg_send(&msg, worker);
    }

    zsocket_destroy(ctx, worker);
    zctx_destroy(&ctx);
    return NULL;
}

// .split main task
// Now we come to the main task. This has the identical functionality to
// the previous {{lbbroker}} broker example, but uses CZMQ to start child
// threads, to hold the list of workers, and to read and send messages:

int main(void)
{
    zctx_t *ctx = zctx_new();
    void *frontend = zsocket_new(ctx, ZMQ_ROUTER);
    assert(frontend);
    void *backend = zsocket_new(ctx, ZMQ_ROUTER);
    assert(backend);

    assert(streq(zsocket_type_str(frontend), "ROUTER"));
    assert(streq(zsocket_type_str(backend), "ROUTER"));

#ifdef WIN32
    const char *interf = "127.0.0.1";
    int frontend_port = 5672;
    int backend_port = 5673;
    int res;

    res = zsocket_bind(frontend, "tcp://%s:%d", interf, frontend_port); // frontend
    assert(res == frontend_port);
    res = zsocket_bind(backend, "tcp://%s:%d", interf, backend_port); // backend
    assert(res == backend_port);
#else
    zsocket_bind(frontend, "ipc://frontend.ipc");
    zsocket_bind(backend, "ipc://backend.ipc");
#endif

    unsigned int fd;
    size_t zmq_fd_size = sizeof(fd);
    if (zmq_getsockopt(backend, ZMQ_RCVHWM, &fd, &zmq_fd_size) == -1)
    {
        printf("haha");
    }

    int client_nbr;
    for (client_nbr = 0; client_nbr < NBR_CLIENTS; client_nbr++)
        zthread_new(client_task, NULL);
    int worker_nbr;
    for (worker_nbr = 0; worker_nbr < NBR_WORKERS; worker_nbr++)
        zthread_new(worker_task, NULL);

    // Queue of available workers
    zlist_t *workers = zlist_new();

    // .split main load-balancer loop
    // Here is the main loop for the load balancer. It works the same way
    // as the previous example, but is a lot shorter because CZMQ gives
    // us an API that does more with fewer calls:
    while (1) {
        zmq_pollitem_t items[] = {
                {backend, 0, ZMQ_POLLIN, 0}, 
                {frontend, 0, ZMQ_POLLIN, 0}
        };
        // Poll frontend only if we have available workers
        int rc = zmq_poll(items, zlist_size(workers) ? 2 : 1, -1);
        if (rc == -1) {
            assert(ENOTSOCK == errno);
            break; // Interrupted
        }

        // Handle worker activity on backend
        if (items[0].revents & ZMQ_POLLIN) {
            // Use worker identity for load-balancing
            zmsg_t *msg = zmsg_recv(backend);
            if (!msg)
                break; // Interrupted
            zframe_t *identity = zmsg_unwrap(msg);
            zlist_append(workers, identity);

            // Forward message to client if it's not a READY
            zframe_t *frame = zmsg_first(msg);
            if (memcmp(zframe_data(frame), WORKER_READY, 1) == 0)
                zmsg_destroy(&msg);
            else
                zmsg_send(&msg, frontend);
        }

        if (items[1].revents & ZMQ_POLLIN) {
            // Get client request, route to first available worker
            zmsg_t *msg = zmsg_recv(frontend);
            if (msg) {
                zmsg_wrap(msg, (zframe_t *)zlist_pop(workers));
                zmsg_send(&msg, backend);
            }
        }
    }

    // When we're done, clean up properly
    while (zlist_size(workers)) {
        zframe_t *frame = (zframe_t *)zlist_pop(workers);
        zframe_destroy(&frame);
    }

    zlist_destroy(&workers);
    zsocket_destroy(ctx, frontend);
    zsocket_destroy(ctx, backend);
    zctx_destroy(&ctx);

    system("pause");
    return 0;
}
// References:
// https://github.com/imatix/zguide/blob/master/examples/C/lbbroker2.c
// http://czmq.zeromq.org/manual:zsocket