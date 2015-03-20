// 2015-01-10T17:48+08:00

// Multithreaded reply

#include "zhelpers.h"

#include <pthread.h>

#ifdef _MSC_VER
# pragma comment(lib, "pthreadVC2.lib")
#endif

static void *step1(void *context)
{
    // Connect to step2 and tell it we're ready
    void *xmitter = zmq_socket(context, ZMQ_PAIR);
    zmq_connect(xmitter, "inproc://step2");
    printf("Step 1 ready, signaling step2...\n");
    s_send(xmitter, "READY");
    zmq_close(xmitter);

    return NULL;
}

static void *step2(void *context)
{
    // Bind inproc socket before starting step1
    void *receiver = zmq_socket(context, ZMQ_PAIR);
    zmq_bind(receiver, "inproc://step2");
    pthread_t thread;
    pthread_create(&thread, NULL, step1, context);

    // Wait for signal and pass it on
    char *string = s_recv(receiver);
    free(string);
    zmq_close(receiver);

    // Connect to step3 and tell it we're ready
    void *xmitter = zmq_socket(context, ZMQ_PAIR);
    zmq_connect(xmitter, "inproc://step3");
    printf("Step 2 ready, signaling step 3\n");
    s_send(xmitter, "READY");
    zmq_close(xmitter);

    return NULL;
}

int main(void)
{
    void *context = zmq_ctx_new();

    // Bind inproc socket before starting step2
    void *receiver = zmq_socket(context, ZMQ_PAIR);
    zmq_bind(receiver, "inproc://step3");

    pthread_t thread;
    pthread_create(&thread, NULL, step2, context);

    // Wait for signal
    char *string = s_recv(receiver);
    free(string);
    zmq_close(receiver);

    printf("Test successful!\n");
    zmq_ctx_destroy(context);

#ifdef _MSC_VER
    system("pause");
#endif
    return 0;
}
