/* 2015-03-02T11:32+08:00 */

/*
This example demonstrates how messages are delivered between REQ and ROUTER
sockets in ZeroMQ.
*/

#include "../../common.h"
#include "../zhelpers.h"

#ifndef USE_LOGICAL_ADDRESS_AS_IDENTITY
# define USE_LOGICAL_ADDRESS_AS_IDENTITY (1)
#endif

typedef struct frame_t {
    void *data;
    int size;
} frame_t;

#define FRAME_INIT NULL, -1,

static frame_t recv_frame(void *socket)
{
    frame_t frame = { FRAME_INIT };
    zmq_msg_t msg;
    int rc;

    rc = zmq_msg_init(&msg);
    assert(rc == 0);

    frame.size = zmq_msg_recv(&msg, socket, 0);
    if (frame.size > 0) {
        frame.data = malloc(frame.size);
        if (frame.data != NULL) {
            memcpy(frame.data, zmq_msg_data(&msg), frame.size);
        } else {
            frame.size = 0;
        }
    }

    rc = zmq_msg_close(&msg);
    assert(rc == 0);

    return frame;
}

#define send_frame(s, f, flag)                 \
    do {                                       \
        if (f.size > 0 && f.data != NULL) {    \
            zmq_send(s, f.data, f.size, flag); \
        } else if (f.size == 0) {              \
            zmq_send(s, "", 0, flag);          \
        }                                      \
    } while (0)

#define free_frame(f)                          \
    do {                                       \
        if (f.size > 0) {                      \
            FREE(f.data);                      \
            f.size = -1;                       \
        }                                      \
    } while (0)

#define dump_frame(f)                          \
    do {                                       \
        assert((f.size > 0 && f.data != NULL)  \
            || f.size == 0);                   \
        s_dump_data(f.data, f.size);           \
    } while (0)

int main(void)
{
    frame_t identity = { FRAME_INIT };
    frame_t delimiter = { FRAME_INIT };
    frame_t body = { FRAME_INIT };

    void *context = zmq_ctx_new();

    void *router = zmq_socket(context, ZMQ_ROUTER);
    void *req = zmq_socket(context, ZMQ_REQ);

#if USE_LOGICAL_ADDRESS_AS_IDENTITY
	/* Specify an user-defined printable logical address as identity. 
	   In reality, we'd allow the ROUTER sockets to invent identities for connections. */
	zmq_setsockopt(req, ZMQ_IDENTITY, "CLIENT", strlen("CLIENT"));
#endif

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

    identity = recv_frame(router);
    dump_frame(identity);

    delimiter = recv_frame(router); /* Frame 2: An empty frame(the frame delimiter) */
    dump_frame(delimiter);
    free_frame(delimiter);

    body = recv_frame(router); /* Frame 3: The real data frame sent by REQ socket */
    dump_frame(body);
    free_frame(body);
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
    send_frame(router, identity, ZMQ_SNDMORE);
    free_frame(identity);
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
[Exploring ROUTER Sockets](http://zguide.zeromq.org/page:all#Exploring-ROUTER-Sockets)
[A-Load Balancing Message Broker](http://zguide.zeromq.org/page:all#A-Load-Balancing-Message-Broker)
[zmq_socket](http://api.zeromq.org/2-1:zmq-socket)
*/
