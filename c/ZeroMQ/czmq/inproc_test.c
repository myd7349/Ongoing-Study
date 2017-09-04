// 2017-09-04T10:30+08:00
// According to the manual:
// http://api.zeromq.org/4-2:zmq-inproc
// >The in-process transport passes messages via memory directly between threads sharing a single 0MQ context.
//
// So:
// 1. `worker_routine_v1` does not work;
// 2. `worker_routine_v2` is fine;
// 3. `worker_routine_v3` is fine;


#include <czmq.h>

#include <pthread.h>

#ifdef _MSC_VER
# pragma warning(disable: 4005) // randof redefined
#endif

#include "zhelpers.h"


void *worker_routine_v1(void *args)
{
    char *reply = NULL;

    void *ctx = zmq_ctx_new();

    void *req = zmq_socket(ctx, ZMQ_REQ);

    int rc = zmq_connect(req, "inproc://backend");
    assert(rc == 0);

    s_send(req, "Hello");
    reply = s_recv(req);
    if (reply) {
        printf("%s\n", reply);
        free(reply);
    }

    zmq_close(req);

    zmq_ctx_term(ctx);

    return NULL;
}


void *worker_routine_v2(void *args)
{
    char *reply = NULL;

    void *ctx = args;
    assert(ctx);

    void *req = zmq_socket(ctx, ZMQ_REQ);

    int rc = zmq_connect(req, "inproc://backend");
    assert(rc == 0);

    s_send(req, "Hello");
    reply = s_recv(req);
    if (reply) {
        printf("%s\n", reply);
        free(reply);
    }

    zmq_close(req);

    return NULL;
}


void *worker_routine_v3(void *args)
{
    zmsg_t *reply = NULL;

    zsock_t *req = zsock_new(ZMQ_REQ);

    int rc = zsock_connect(req, "inproc://backend");
    assert(rc == 0);

    zstr_send(req, "Hello");

    reply = zmsg_recv(req);
    if (reply) {
        zmsg_print(reply);
        zmsg_destroy(&reply);
    }

    zsock_destroy(&req);

    return NULL;
}


int main(void)
{
    pthread_t client;

    void *ctx = zsys_init();

    zmsg_t *request = NULL;

    zsock_t *rep = zsock_new(ZMQ_REP);
    
    int rc = zsock_bind(rep, "inproc://backend");
    assert(rc == 0);
    
#if 0
    pthread_create(&client, NULL, worker_routine_v1, ctx);
#elif 1
    pthread_create(&client, NULL, worker_routine_v2, ctx);
#else
    pthread_create(&client, NULL, worker_routine_v3, ctx);
#endif

    request = zmsg_recv(rep);
    if (request) {
        zmsg_print(request);
        zmsg_destroy(&request);
    }

    zstr_send(rep, "Yes! That's my answer.");

    zsock_destroy(&rep);

#if defined __WINDOWS__
    zsys_shutdown();
#endif

    return 0;
}
