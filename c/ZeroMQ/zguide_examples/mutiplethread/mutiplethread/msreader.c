// 2014-12-24T09:46+08:00
#include "zhelpers.h"

#include <errno.h>

static char *
s_recv_ex(void *socket, int flag) {
    char buffer[256];
    int size = zmq_recv(socket, buffer, 255, flag);
    if (size == -1)
        return NULL;
    if (size > 255)
        size = 255;
    buffer[size] = 0;
    return strdup(buffer);
}

int main(void)
{
    // connect to task ventilator
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    // connect to weather server
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

    // process messages from both sockets
    // we prioritize traffic from the task ventilator
    while (1) {
        char *msg = s_recv_ex(receiver, ZMQ_DONTWAIT);
        if (msg != NULL) {
            puts(msg);
            free(msg);
        }

        msg = s_recv_ex(subscriber, ZMQ_DONTWAIT);
        if (msg != NULL) {
            puts(msg);
            free(msg);
        }
        // No activity, so sleep for 1 msec
        Sleep(1);
    }
    zmq_close(receiver);
    zmq_close(subscriber);
    zmq_ctx_destroy(context);

    return 0;
}