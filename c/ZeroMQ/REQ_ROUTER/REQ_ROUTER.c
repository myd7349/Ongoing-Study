/* 2015-03-02T11:32+08:00 */

/*
This example demonstrates how messages are delivered between REQ and ROUTER
sockets in ZeroMQ.
*/

#include "../../common.h"
#include "../zhelpers.h"

int main(void)
{
    char *identity = NULL;
    char *delimiter = NULL;
    char *data = NULL;

    void *context = zmq_ctx_new();

    void *router = zmq_socket(context, ZMQ_ROUTER);
    void *req = zmq_socket(context, ZMQ_REQ);

    /* In reality, we'd allow the ROUTER sockets to invent identities for connections. */
    zmq_setsockopt(req, ZMQ_IDENTITY, "CLIENT", strlen("CLIENT"));

    zmq_bind(router, "inproc://reqvsrouter");
    zmq_connect(req, "inproc://reqvsrouter");

    /* ---------- REQ -> ROUTER Begin ---------- */
    puts("----------------------------------------");
    /*
    1. When sending a message via a REQ socket:
         The REQ socket will prepend the message an empty frame(the delimiter). 
         So we got a two-frame message:
           Frame 1: Empty delimiter frame(automatic prepended by REQ socket)
           Frame 2: Data frame to send
         And this two-frame message is delivered to ROUTER socket.

    2. When the two-frame message arrives at ROUTER socket, a ZMQ_ROUTER socket 
       shall prepend a message part containing the identity of the originating 
       peer to the message before passing it to the application.

       That is, when our application receives messages off a ROUTER socket, it
       will get a three-frame message.
         Frame 1: Identity of the connection(prepended by ROUTER socket)
         Frame 2: Empty delimiter frame
         Frame 3: Data frame

    Note that all frames in 0MQ are length-specified frame.
    */
    s_send(req, "Hello");

    identity = s_recv(router); /* Frame 1: Identity frame */
    s_dump_data(identity, strlen(identity));

    delimiter = s_recv(router); /* Frame 2: An empty frame(the frame delimiter) */
    s_dump_data(delimiter, strlen(delimiter));
    assert(0 == *delimiter);
    FREE(delimiter);

    data = s_recv(router); /* Frame 3: The real data frame sent by REQ socket */
    s_dump_data(data, strlen(data));
    FREE(data);
    /* ----------- REQ -> ROUTER End ----------- */

    /* ---------- ROUTER -> REQ Begin ---------- */
    /*
    1. Send a message via a ROUTER socket:
         Firstly, we send an identity frame;
         Secondly, a frame delimiter;
         Thirdly, the data frame;
       Then the ZMQ_ROUTER socket shall remove the first part of the message 
       and use it to determine the identity of the peer the message shall be 
       routed to.
    2. The REQ socket picks this message(a two-frame message) up, and checks 
       that the first frame is the empty delimiter, which it is. The REQ socket 
       discards that frame and passes "World" to the calling application
    */
    s_sendmore(router, identity);
    FREE(identity);
    s_sendmore(router, "");
    s_send(router, "World");

    s_dump(req);
    /* ----------- ROUTER -> REQ End ----------- */

    zmq_close(req);
    zmq_close(router);
    zmq_ctx_destroy(context);

    PAUSE();
    return 0;
}
/*
References:
[identity.c](https://github.com/imatix/zguide/blob/master/examples/C/identity.c)
[lbbroker.c](https://github.com/imatix/zguide/blob/master/examples/C/lbbroker.c)
[The REQ to ROUTER Combination](http://zguide.zeromq.org/page:all#The-REQ-to-ROUTER-Combination)
[The Simple Reply Envelope](http://zguide.zeromq.org/page:all#The-Simple-Reply-Envelope)
[The Extended Reply Envelope](http://zguide.zeromq.org/page:all#The-Extended-Reply-Envelope)
[What's This Good For](http://zguide.zeromq.org/page:all#What-s-This-Good-For)
[Recap of Request Reply Sockets](http://zguide.zeromq.org/page:all#Recap-of-Request-Reply-Sockets)
[Request Reply Combinations](http://zguide.zeromq.org/page:all#Request-Reply-Combinations)
[A-Load Balancing Message Broker](http://zguide.zeromq.org/page:all#A-Load-Balancing-Message-Broker)
[zmq_socket](http://api.zeromq.org/2-1:zmq-socket)
*/
