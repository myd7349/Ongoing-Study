// 2014-12-22T14:26+08:00
// Hello world client
#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
# define sleep Sleep
# include <stdlib.h>
# define PAUSE() system("pause")
#else
# include <unistd.h>
# define PAUSE() __noop
#endif

#include <zmq.h>

int main(void)
{
    printf("Connecting to hello world server...\n");
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer[10];
        printf("Sending Hello %d...\n", request_nbr);
        zmq_send(requester, "Hello", 5, 0);
        zmq_recv(requester, buffer, 10, 0);
        printf("Received World %d\n", request_nbr);
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);

    PAUSE();
    return 0;
}