#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zmq.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"


#define MAX_MSG_LEN (1024 * 128)
#define READY_MSG   ("Pink Floyd: Time")


#define FATAL_ERROR(func_name) \
    do \
    { \
        fprintf(stderr, "%s(%d): %s failed(%d): %s.\n", __FILE__, __LINE__, (func_name), errno, strerror(errno)); \
        exit(EXIT_FAILURE); \
    } while (0)


void stack_free(void *data, void *hint)
{
    (void *)data;
    (void *)hint;
}


void the_starting_gun(void *rep)
{
    zmq_msg_t msg;
    int result;

    if (zmq_msg_init_size(&msg, strlen(READY_MSG) + 1) != 0)
        FATAL_ERROR("zmq_msg_init_size");
    result = zmq_msg_recv(&msg, rep, 0);
    if (result == -1)
        FATAL_ERROR("zmq_msg_recv");
    assert(result == strlen(READY_MSG) + 1);
    assert(strcmp(zmq_msg_data(&msg), READY_MSG) == 0);
    zmq_msg_close(&msg);

    if (zmq_msg_init_data(&msg, READY_MSG, strlen(READY_MSG) + 1, stack_free, NULL) != 0)
        FATAL_ERROR("zmq_msg_init_data");
    if (zmq_msg_send(&msg, rep, 0) == -1)
        FATAL_ERROR("zmq_msg_send");
    zmq_msg_close(&msg);

    puts("Hey you! Do not help them to bury the light.");
}


int main()
{
    int64_t bytes_sent = 0;
    int64_t ellapsed_ms;
    long double data_rate_Bps;
    high_timer_t timer;
    char reply_msg[MAX_MSG_LEN] = "";
    int result;

    zmq_msg_t msg;

    void *ctx = zmq_ctx_new();
    if (ctx == NULL)
    {
        fprintf(stderr, "zmq_ctx_new failed.\n");
        return EXIT_FAILURE;
    }

    void *rep = zmq_socket(ctx, ZMQ_REP);
    if (rep == NULL)
    {
        fprintf(stderr, "zmq_socket failed(%d): %s.\n", errno, strerror(errno));
        zmq_ctx_shutdown(ctx);
        return EXIT_FAILURE;
    }

    if (zmq_bind(rep, "tcp://*:5678") == -1)
        FATAL_ERROR("zmq_bind");

    the_starting_gun(rep);

    high_timer_start(&timer);

    while (1)
    {
        zmq_msg_init(&msg);
        if (zmq_msg_recv(&msg, rep, 0) == -1)
            FATAL_ERROR("zmq_msg_recv");

        if (zmq_msg_size(&msg) == 1 && *(const char *)zmq_msg_data(&msg) == 'Q')
        {
            zmq_msg_close(&msg);
            puts("Received 'Q' from client.");

            if (zmq_msg_init_size(&msg, 1) != 0)
                FATAL_ERROR("zmq_msg_init_size");
            *(char *)zmq_msg_data(&msg) = 'Q';
            if (zmq_msg_send(&msg, rep, 0) == -1)
                FATAL_ERROR("zmq_msg_send");
            zmq_msg_close(&msg);

            break;
        }
        else
        {
            zmq_msg_close(&msg);

#if 1
            if (zmq_msg_init_data(&msg, reply_msg, sizeof(reply_msg), stack_free, NULL) == -1)
                FATAL_ERROR("zmq_msg_init_data");
#else
            if (zmq_msg_init_size(&msg, MAX_MSG_LEN) == -1)
                FATAL_ERROR("zmq_msg_init_size");
#endif
            result = zmq_msg_send(&msg, rep, 0);
            if (result == -1)
                FATAL_ERROR("zmq_msg_send");
            bytes_sent += result;
            zmq_msg_close(&msg);
        }
    }

    ellapsed_ms = high_timer_ellapsed_ms(&timer);
    data_rate_Bps = bytes_sent * 1000.0L / ellapsed_ms;

    printf(
        "Total sent: %" PRId64 " bytes | %.2Lf KiB | %.2Lf MiB\n"
        "Times ellipsed: %" PRId64 " ms\n"
        "Data Rate: %.2Lf %s | %.2Lf %s | %.2Lf %s | %.2Lf %s\n",
        bytes_sent, bytes_sent / 1024.0L, bytes_sent / 1024.0L / 1024.0,
        ellapsed_ms,
        data_rate_Bps, data_rate_unit_name(Bps),
        data_rate_convertf(data_rate_Bps, Bps, Gbps), data_rate_unit_name(Gbps),
        data_rate_convertf(data_rate_Bps, Bps, KiBps), data_rate_unit_name(KiBps),
        data_rate_convertf(data_rate_Bps, Bps, MiBps), data_rate_unit_name(MiBps)
    );

    zmq_close(rep);

    zmq_ctx_shutdown(ctx);

    return 0;
}


// References:
// https://github.com/nanomsg/nng/issues/560
