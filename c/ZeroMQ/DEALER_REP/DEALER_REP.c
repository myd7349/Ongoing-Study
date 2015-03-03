/* 2015-03-02T16:46+08:00 */

/*
This example demonstrates how messages are delivered between DEALER and REP
in ZeroMQ. That is, what do the envelopes on the wire created by DEALER and 
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
    /*
    The document of zmq_socket says that:
    When a ZMQ_DEALER socket is connected to a ZMQ_REP socket each message
    sent must consist of an empty message part, the delimiter, followed by 
    one or more body parts.

    0MQ - The Guide/The Simple Reply Envelope:
    The REP socket does the matching work: it strips off the envelope, up to 
    and including the delimiter frame, saves the whole envelope, and passes 
    the "Hello" string up the application.
    */
    
    // s_sendmore(dealer, "PSEUDO-ADDR");
    s_sendmore(dealer, "");
#if 0
    s_sendmore(dealer, "Hello");
#endif
    s_send(dealer, "Hello");
    s_dump(rep);

    /* -------------------- REP -> DEALER -------------------- */
    /*
    0MQ - The Guide/The Extended Reply Envelope:
    When REP sends "World" back, the REP socket wraps that with the envelope
    it saved, and sends a reply message across the wire to the DEALER socket.

    In this example, cause no identity frame exists, so this reply message is 
    a two-frame message. But note that this is not always the case. For example,
    in the "REQ <-> ROUTER | DEALER <-> REP" pattern, the reply message is a
    three-frame message.

    If we uncomment this line above:
        // s_sendmore(dealer, "PSEUDO-ADDR");
    then the reply message sent back by REP socket will be a three-frame message.
    */
    s_send(rep, "World");
    s_dump(dealer);

    /*
    Conclusion:
    The DEALER never touch the incoming message, and the outgoing message sent
    by DEALER socket is identical to the incoming message.

    REP socket, however, will strip off the whole envelope and save it. When 
    REP's work is done, it will wraps that envelope with the message body and
    send it back.
    */

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
[The Extended Reply Envelope](http://zguide.zeromq.org/page:all#The-Extended-Reply-Envelope)
[Pub Sub Message Envelopes](http://zguide.zeromq.org/page:all#Pub-Sub-Message-Envelopes)
[A Load Balancing Message Broker](http://zguide.zeromq.org/page:all#A-Load-Balancing-Message-Broker)
[zmq_ctx_term vs zmq_ctx_destroy vs zmq_ctx_shutdown](http://lists.zeromq.org/pipermail/zeromq-dev/2014-June/026403.html)
[zmq_socket](http://api.zeromq.org/2-1:zmq-socket)
*/