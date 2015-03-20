// 2015-01-13T11:05+08:00

#include "zhelpers.h"

int main(void)
{
    // Prepare our context and subscriber
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5563");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "B", 1);

    while (1) {
        // Read envelope with address
        char *address = s_recv(subscriber);
        // Read messages contents
        char *contents = s_recv(subscriber);
        printf("[%s] %s\n", address, contents);
        free(address);
        free(contents);
    }
    // We never get here, but clean up anyhow
    zmq_close(subscriber);
    zmq_ctx_destroy(context);

    return 0;
}