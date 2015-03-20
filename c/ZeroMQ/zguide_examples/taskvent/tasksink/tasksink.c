// 2014-12-25T16:34+08:00
#include "zhelpers.h"

int main(void)
{
    // prepare our context and socket
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_bind(receiver, "tcp://*:5558");

    // wait for start of batch
    char *string = s_recv(receiver);
    free(string);

    // start our clock now
    int64_t start_time = s_clock();

    // process 100 confirmations
    int task_nbr;
    for (task_nbr = 0; task_nbr < 100; ++task_nbr) {
        char *string = s_recv(receiver);
        free(string);
        if ((task_nbr / 10) * 10 == task_nbr) {
            printf(":");
        } else {
            printf(".");
        }
        fflush(stdout);
    }

    // calculate and report duration of batch
    printf("Total elapsed time: %d msec\n",
        (int)(s_clock() - start_time));

    zmq_close(receiver);
    zmq_ctx_destroy(context);
    return 0;
}