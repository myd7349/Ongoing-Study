// 2014-12-23T11:02+08:00
#include "zhelpers.h"

int main(void)
{
    // socket to receive messages on
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    // socket to send messages to
    void *sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:5558");

    // process tasks forever
    while (1) {
        char *string = s_recv(receiver);
        printf("%s.", string); // show process
        fflush(stdout);
        Sleep(atoi(string)); // do the work
        free(string);
        s_send(sender, ""); // send results to sink
    }

    zmq_close(receiver);
    zmq_close(sender);
    zmq_ctx_destroy(context);

    return 0;
}