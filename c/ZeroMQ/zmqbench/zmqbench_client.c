#include <errno.h>
#include <inttypes.h>
#include <limits.h>
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


void wait_for_the_starting_gun(void *req)
{
    zmq_msg_t msg;
    int result;

    if (zmq_msg_init_data(&msg, READY_MSG, strlen(READY_MSG) + 1, stack_free, NULL) != 0)
        FATAL_ERROR("zmq_msg_init_data");
    if (zmq_msg_send(&msg, req, 0) == -1)
        FATAL_ERROR("zmq_msg_send");
    zmq_msg_close(&msg);

    if (zmq_msg_init_size(&msg, strlen(READY_MSG) + 1) != 0)
        FATAL_ERROR("zmq_msg_init_size");
    result = zmq_msg_recv(&msg, req, 0);
    if (result == -1)
        FATAL_ERROR("zmq_msg_recv");
    assert(result == strlen(READY_MSG) + 1);
    assert(strcmp(zmq_msg_data(&msg), READY_MSG) == 0);
    zmq_msg_close(&msg);

    puts(
        "And you run and you run to catch up with the sun, but it's sinking\n"
        "And racing around to come up behind you again\n"
        "The sun is the same in the relative way, but you're older\n"
        "Shorter of breath and one day closer to death"
    );
}


int main(int argc, char *argv[])
{
    int quit = 0;
    int total_bytes = 256 * 1024 * 1024;
    int turns = total_bytes / MAX_MSG_LEN;
    int result;
    int64_t total_bytes_received = 0;
    int64_t ellapsed_ms;
    long double data_rate_Bps;
    high_timer_t timer;
    char remote_endpoint[260] = "";

    void *ctx;
    void *req;
    zmq_msg_t msg;

    if (argc == 1)
    {
        strcpy(remote_endpoint, "tcp://localhost:5678");
    }
    else if (argc == 2)
    {
        unsigned short ip_addr[4] = { 260, 260, 260, 260 };
        unsigned int port = 65537;

        //sscanf(argv[1], "%hu%*[^.].%hu%*[^.].%hu%*[^.].%hu%*[^:]:%u",
        sscanf(argv[1], "%hu . %hu . %hu . %hu : %u",
            ip_addr + 0, ip_addr + 1, ip_addr + 2, ip_addr + 3, &port);

        if (ip_addr[0] == 260 || ip_addr[0] == 260 || ip_addr[0] == 260 || ip_addr[0] == 260 || port > USHRT_MAX)
        {
#ifndef NDEBUG
            printf("%hu.%hu.%hu.%hu:%u\n", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3], port);
#endif
            puts("Usage:\n  zmqbench_client <*.*.*.*:port>\n  (Example: zmqbench_client 127.0.0.1:5678)");
            return 1;
        }

        sprintf(remote_endpoint, "tcp://%hu.%hu.%hu.%hu:%u",
            ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3], port);

        printf("Remote endpoint: %s\n", remote_endpoint);
    }
    else
    {
        puts("Usage:\n  zmqbench_client <host:port>");
        return 1;
    }

    ctx = zmq_ctx_new();
    if (ctx == NULL)
    {
        fprintf(stderr, "zmq_ctx_new failed.\n");
        return EXIT_FAILURE;
    }

    req = zmq_socket(ctx, ZMQ_REQ);
    if (req == NULL)
    {
        fprintf(stderr, "zmq_socket failed(%d): %s.\n", errno, strerror(errno));
        zmq_ctx_shutdown(ctx);
        return EXIT_FAILURE;
    }

    if (zmq_connect(req, remote_endpoint) != 0)
    {
        fprintf(stderr, "zmq_connect failed(%d): %s.\n", errno, strerror(errno));
        zmq_close(req);
        zmq_ctx_shutdown(ctx);
        return EXIT_FAILURE;
    }

    wait_for_the_starting_gun(req);

    high_timer_start(&timer);

    while (1)
    {
        if (zmq_msg_init_size(&msg, 1) != 0)
            FATAL_ERROR("zmq_msg_init_size");
        *(char *)zmq_msg_data(&msg) = (turns-- == 0 ? 'Q' : 'Y');
        if (zmq_msg_send(&msg, req, 0) == -1)
            FATAL_ERROR("zmq_msg_send");
        zmq_msg_close(&msg);

        zmq_msg_init(&msg);
        result = zmq_msg_recv(&msg, req, 0);
        if (result == -1)
        {
            FATAL_ERROR("zmq_msg_recv");
        }
        else if (result == 1 && *(const char *)zmq_msg_data(&msg) == 'Q')
        {
            puts("Received 'Q' from server.");
            zmq_msg_close(&msg);
            break;
        }
        else
        {
            total_bytes_received += result;
            zmq_msg_close(&msg);
        }
    }

    ellapsed_ms = high_timer_ellapsed_ms(&timer);
    data_rate_Bps = total_bytes_received * 1000.0L / ellapsed_ms;

    printf(
        "Total received: %" PRId64 " bytes | %.2Lf KiB | %.2Lf MiB\n"
        "Times ellipsed: %" PRId64 " ms\n"
        "Data Rate: %.2Lf %s | %.2Lf %s | %.2Lf %s | %.2Lf %s\n",
        total_bytes_received, total_bytes_received / 1024.0L, total_bytes_received / 1024.0L / 1024.0,
        ellapsed_ms,
        data_rate_Bps, data_rate_unit_name(Bps),
        data_rate_convertf(data_rate_Bps, Bps, Gbps), data_rate_unit_name(Gbps),
        data_rate_convertf(data_rate_Bps, Bps, KiBps), data_rate_unit_name(KiBps),
        data_rate_convertf(data_rate_Bps, Bps, MiBps), data_rate_unit_name(MiBps)
    );

    zmq_close(req);

    zmq_ctx_shutdown(ctx);

    return 0;
}


// References:
// https://www.cnblogs.com/fullsail/p/4285215.html
// https://github.com/nanomsg/nng/issues/560
