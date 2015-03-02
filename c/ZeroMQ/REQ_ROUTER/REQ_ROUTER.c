/* 2015-03-02T11:32+08:00 */

/*
This example demonstrates how messages are delivered between REQ and ROUTER
sockets in ZeroMQ.
*/
#include "zhelpers.h"

#include "../../common.h"

int main(void)
{
    char *identity = NULL;
    char *delimiter = NULL;
    char *data = NULL;

    void *context = zmq_ctx_new();

    void *router = zmq_socket(context, ZMQ_ROUTER);
    void *req = zmq_socket(context, ZMQ_REQ);

    zmq_setsockopt(req, ZMQ_IDENTITY, "CLIENT", strlen("CLIENT"));

    zmq_bind(router, "inproc://reqvsrouter");
    zmq_connect(req, "inproc://reqvsrouter");

    /*
    REQ -> ROUTER
    */
    s_send(req, "Hello from REQ!");

    puts("----------------------------------------");

    identity = s_recv(router);
    s_dump_data(identity, strlen(identity));

    delimiter = s_recv(router);
    s_dump_data(delimiter, strlen(delimiter));
    assert(0 == *delimiter);
    FREE(delimiter);

    data = s_recv(router);
    s_dump_data(data, strlen(data));
    FREE(data);

    /*
    ROUTER -> REQ 
    */
    s_sendmore(router, identity);
    FREE(identity);
    s_sendmore(router, "");
    s_send(router, "Reply from ROUTER!");

    s_dump(req);

    /* REQ -> ROUTER again! */
    s_send(req, "Goodbye from REQ!");
    s_dump(router);

    zmq_close(req);
    zmq_close(router);
    zmq_ctx_destroy(context);

    PAUSE();
    return 0;
}
/*
References:
[zguide](http://zguide.zeromq.org/page:all)
[zmq_socket](http://api.zeromq.org/2-1:zmq-socket)
*/
