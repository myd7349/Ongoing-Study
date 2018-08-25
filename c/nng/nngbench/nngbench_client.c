#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nng/nng.h>
#include <nng/protocol/reqrep0/req.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"

#define MAX_MSG_LEN (1024 * 128)
#define READY_MSG   ("Pink Floyd: Time")


#define FATAL_ERROR(func_name, result) \
    do \
    { \
        fprintf(stderr, "%s(%d): %s: %s(%d)\n", __FILE__, __LINE__, (func_name), nng_strerror((result)), (result)); \
        exit(EXIT_FAILURE); \
    } while (0)


void wait_for_the_starting_gun(nng_socket socket)
{
#if USE_NNG_FLAG_ALLOC
    void *msg = NULL;
#else
    char msg[260];
#endif
    size_t bytes;
    int result;

    if ((result = nng_send(socket, READY_MSG, strlen(READY_MSG) + 1, 0)) != 0)
        FATAL_ERROR("nng_send", result);

#if USE_NNG_FLAG_ALLOC
    if ((result = nng_recv(socket, &msg, &bytes, NNG_FLAG_ALLOC)) != 0)
#else
    bytes = sizeof(msg);
    if ((result = nng_recv(socket, msg, &bytes, 0)) != 0)
#endif
        FATAL_ERROR("nng_recv", result);

    assert(bytes == strlen(READY_MSG) + 1);
    assert(strcmp(msg, READY_MSG) == 0);

#if USE_NNG_FLAG_ALLOC
    nng_free(msg, bytes);
#endif

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
    int64_t total_bytes_received = 0;
    int64_t ellapsed_ms;
    long double data_rate_Bps;
    high_timer_t timer;
    char remote_endpoint[260] = "";

#if USE_NNG_FLAG_ALLOC
    void *msg = NULL;
#else
    char msg[MAX_MSG_LEN];
#endif

    size_t bytes;

    nng_socket socket;
    int result;

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

    if ((result = nng_req0_open(&socket)) != 0)
        FATAL_ERROR("nng_req0_open", result);

    if ((result = nng_dial(socket, remote_endpoint, NULL, 0)) != 0)
        FATAL_ERROR("nng_dial", result);

    wait_for_the_starting_gun(socket);

    high_timer_start(&timer);

    while (1)
    {
        if ((result = nng_send(socket, (turns-- == 0 ? "Q" : "Y"), 1, 0)) != 0)
            FATAL_ERROR("nng_send", result);

#if USE_NNG_FLAG_ALLOC
        if ((result = nng_recv(socket, &msg, &bytes, NNG_FLAG_ALLOC)) != 0)
#else
        bytes = sizeof(msg);
        if ((result = nng_recv(socket, msg, &bytes, 0)) != 0)
#endif
            FATAL_ERROR("nng_recv", result);

        if (bytes == 1 && *(const char *)msg == 'Q')
        {
#if USE_NNG_FLAG_ALLOC
            nng_free(msg, bytes);
#endif

            puts("Received 'Q' from server.");
            break;
        }
        else
        {
#if USE_NNG_FLAG_ALLOC
            nng_free(msg, bytes);
#endif

            total_bytes_received += bytes;
        }
    }

    ellapsed_ms = high_timer_ellapsed_ms(&timer);
    data_rate_Bps = total_bytes_received * 1000.0L / ellapsed_ms;

    nng_close(socket);

    printf(
        "Total received: %lld bytes | %.2Lf KiB | %.2Lf MiB\n"
        "Times ellipsed: %lld ms\n"
        "Data Rate: %.2Lf %s | %.2Lf %s | %.2Lf %s | %.2Lf %s\n",
        total_bytes_received, total_bytes_received / 1024.0L, total_bytes_received / 1024.0L / 1024.0,
        ellapsed_ms,
        data_rate_Bps, data_rate_unit_name(Bps),
        data_rate_convertf(data_rate_Bps, Bps, Gbps), data_rate_unit_name(Gbps),
        data_rate_convertf(data_rate_Bps, Bps, KiBps), data_rate_unit_name(KiBps),
        data_rate_convertf(data_rate_Bps, Bps, MiBps), data_rate_unit_name(MiBps)
    );

    return 0;
}


// References:
// https://nanomsg.org/gettingstarted/nng/reqrep.html
// https://www.cnblogs.com/fullsail/p/4285215.html
// https://nanomsg.github.io/nng/man/v1.0.0/nng_recv.3.html
