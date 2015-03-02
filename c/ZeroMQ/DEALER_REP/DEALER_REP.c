/* 2015-03-02T16:46+08:00 */

/*
This example demonstrates how messages are delivered between DEALER and REP
in ZeroMQ. That is, what do the envelope on the wire created by DEALER and 
REP look like?
*/

#include "../../common.h"
#include "../zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();

    void *dealer = zmq_socket(context, ZMQ_DEALER);
    void *rep = zmq_socket(context, ZMQ_REP);

    /*
    Either side can bind in this example. Just keep in mind that the server side
    (here, `the server side` means the side that calls zmq_bind, not the side that
    provides some kind of service) is the static component in the messaging topology
    and the client side is the dynamic component.
    */
#if 0
    zmq_bind(dealer, "inproc://dealervsrep");
    zmq_connect(rep, "inproc://dealervsrep");
#else
    zmq_bind(rep, "inproc://dealervsrep");
    zmq_connect(dealer, "inproc://dealervsrep");
#endif

    /* -------------------- DEALER -> REP -------------------- */
    s_sendmore(dealer, "");
    s_send(dealer, "Hello");
    s_dump(rep);

    /* -------------------- REP -> DEALER -------------------- */
    s_send(rep, "World");
    s_dump(dealer);

    zmq_close(rep);
    zmq_close(dealer);
    zmq_ctx_term(context);
    PAUSE();
    return 0;
}

/*
References:
[ZMQ REP, knowing who send the request](http://stackoverflow.com/questions/11786160/zmq-rep-knowing-who-send-the-request)
[Does PyZMQ handle creating threads for each new client connection?](http://stackoverflow.com/questions/13124359/does-pyzmq-handle-creating-threads-for-each-new-client-connection)
[ZeroMQ Request-Reply Pattern](http://rfc.zeromq.org/spec:28)
[The REQ to REP Combination](http://zguide.zeromq.org/page:all#The-REQ-to-REP-Combination)
[The Request Reply Mechanisms](http://zguide.zeromq.org/page:all#The-Request-Reply-Mechanisms)
[The Simple Reply Envelope](http://zguide.zeromq.org/page:all#The-Simple-Reply-Envelope)
[Pub Sub Message Envelopes](http://zguide.zeromq.org/page:all#Pub-Sub-Message-Envelopes)
[A Load Balancing Message Broker](http://zguide.zeromq.org/page:all#A-Load-Balancing-Message-Broker)
[zmq_ctx_term vs zmq_ctx_destroy vs zmq_ctx_shutdown](http://lists.zeromq.org/pipermail/zeromq-dev/2014-June/026403.html)
[zmq_socket](http://api.zeromq.org/2-1:zmq-socket)
*/