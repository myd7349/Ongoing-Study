// 2014-12-24T10:26+08:00
#include "zhelpers.h"

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

    // Process messages from both sockets
    while (1) {
        char msg[256];
        zmq_pollitem_t items[] = {
                { receiver, 0, ZMQ_POLLIN, 0 },
                { subscriber, 0, ZMQ_POLLIN, 0 },
        };
        zmq_poll(items, 2, -1);
        if (items[0].revents & ZMQ_POLLIN) {
            int size = zmq_recv(receiver, msg, 255, 0);
            if (size != -1) {
                break;
            }
        }
        if (items[1].revents & ZMQ_POLLIN) {
            //int size = zmq_recv(subscriber, msg, 255, 0);
            char *msg = s_recv(subscriber);
            if (msg != NULL) {
                // process weather update
                puts(msg);
                free(msg);
            }
        }
    }
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}
