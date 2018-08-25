#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"


#define MAX_MSG_LEN (1024 * 128)
#define READY_MSG   ("Pink Floyd: Time")


#define FATAL_ERROR(func_name, error) \
    do \
    { \
        fprintf(stderr, "%s(%d): %s: %s(%d)\n", __FILE__, __LINE__, (func_name), nng_strerror((error)), (error)); \
        exit(EXIT_FAILURE); \
    } while (0)


void the_starting_gun(nng_socket socket)
{
    int result;
#if USE_NNG_FLAG_ALLOC
    void *msg = NULL;
#else
    char msg[256];
#endif
    size_t bytes;

#if USE_NNG_FLAG_ALLOC
    if ((result = nng_recv(socket, &msg, &bytes, NNG_FLAG_ALLOC)) != 0)
#else
    bytes = sizeof(msg);
    if ((result = nng_recv(socket, msg, &bytes, 0)) != 0)
#endif
        FATAL_ERROR("nng_recv", result);

    assert(bytes == strlen(READY_MSG) + 1);
    assert(strcmp(msg, READY_MSG) == 0);

    if ((result = nng_send(socket, msg, strlen(READY_MSG) + 1, 0)) != 0)
        FATAL_ERROR("nng_send", result);

    puts("Hey you! Do not help them to bury the light.");
}


int main()
{
    int64_t bytes_sent = 0;
    int64_t ellapsed_ms;
    long double data_rate_Bps;
    high_timer_t timer;

    void *request_msg = NULL;
    char reply_msg[MAX_MSG_LEN] = "";

    size_t size;

    nng_socket socket;
    int result;

    if ((result = nng_rep0_open(&socket)) != 0)
        FATAL_ERROR("nng_rep0_open", result);

    if ((result = nng_listen(socket, "tcp://*:5678", NULL, 0)) != 0)
        FATAL_ERROR("nng_listen", result);

    the_starting_gun(socket);

    high_timer_start(&timer);

    while (1)
    {
        if ((result = nng_recv(socket, &request_msg, &size, NNG_FLAG_ALLOC)) != 0)
            FATAL_ERROR("nng_recv", result);

        if (size == 1 && *(const char *)request_msg == 'Q')
        {
            puts("Received 'Q' from client.");
            nng_free(request_msg, size);

            if ((result = nng_send(socket, "Q", 1, 0)) != 0)
                FATAL_ERROR("nng_send", result);

            break;
        }
        else
        {
            nng_free(request_msg, size);

            if ((result = nng_send(socket, reply_msg, sizeof(reply_msg), 0)) != 0)
                FATAL_ERROR("nng_send", result);

            bytes_sent += sizeof(reply_msg);
        }
    }

    ellapsed_ms = high_timer_ellapsed_ms(&timer);
    data_rate_Bps = bytes_sent * 1000.0L / ellapsed_ms;

    nng_close(socket);

    printf(
        "Total sent: %lld bytes | %.2Lf KiB | %.2Lf MiB\n"
        "Times ellipsed: %lld ms\n"
        "Data Rate: %.2Lf %s | %.2Lf %s | %.2Lf %s | %.2Lf %s\n",
        bytes_sent, bytes_sent / 1024.0L, bytes_sent / 1024.0L / 1024.0,
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
