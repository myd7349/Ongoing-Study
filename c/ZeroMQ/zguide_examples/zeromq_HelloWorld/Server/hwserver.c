// 2014-12-22T14:05+08:00
// Hello world server
#include <assert.h>
#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
# define sleep Sleep

# pragma comment(lib, "libzmq-v120-mt-4_0_4.lib")
#else
# include <unistd.h>
#endif

#include <zmq.h>

int main(void)
{
    // Socket to talk to clients
    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:5555");
    assert(rc == 0);

    while (1) {
        char buffer[10];
        zmq_recv(responder, buffer, 10, 0);
        printf("Received Hello\n");
        sleep(1);
        zmq_send(responder, "World", 5, 0);
    }
    return 0;
}