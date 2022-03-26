#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"


#define MAX_MSG_LEN (1024 * 128)
#define READY_MSG   ("Pink Floyd: Time")


#define FATAL_ERROR(func_name) \
    do \
    { \
        fprintf(stderr, "%s(%d): %s: %s\n", __FILE__, __LINE__, func_name, nn_strerror(nn_errno())); \
        exit(EXIT_FAILURE); \
    } while (0)


void the_starting_gun(int socket)
{
    int bytes;
    char msg[256];

    if ((bytes = nn_recv(socket, msg, sizeof(msg), 0)) < 0)
        FATAL_ERROR("nn_recv");

    assert(bytes == strlen(READY_MSG) + 1);
    assert(strcmp(msg, READY_MSG) == 0);

    if ((bytes = nn_send(socket, msg, bytes, 0)) < 0)
        FATAL_ERROR("nn_send");

    puts("Hey you! Do not help them to bury the light.");
}


int main()
{
    int64_t bytes_sent = 0;
    int64_t elapsed_ms;
    long double data_rate_Bps;
    high_timer_t timer;
    char reply_msg[MAX_MSG_LEN] = "";

    int socket;
    int result;

    if ((socket = nn_socket(AF_SP, NN_REP)) < 0)
        FATAL_ERROR("nn_socket");

    if ((result = nn_bind(socket, "tcp://*:5678")) < 0)
        FATAL_ERROR("nn_bind");

    the_starting_gun(socket);

    high_timer_start(&timer);

    while (1)
    {
        if ((result = nn_recv(socket, reply_msg, sizeof(reply_msg), 0)) < 0)
            FATAL_ERROR("nn_recv");

        if (result == 1 && reply_msg[0] == 'Q')
        {
            puts("Received 'Q' from client.");

            if ((result = nn_send(socket, "Q", 1, 0)) < 0)
                FATAL_ERROR("nn_send");

            break;
        }
        else
        {
            if ((result = nn_send(socket, reply_msg, sizeof(reply_msg), 0)) < 0)
                FATAL_ERROR("nn_send");

            bytes_sent += result;
        }
    }

    nn_close(socket);

    elapsed_ms = high_timer_elapsed_ms(&timer);
    data_rate_Bps = bytes_sent * 1000.0L / elapsed_ms;

    printf(
        "Total sent: %" PRId64 " bytes | %.2Lf KiB | %.2Lf MiB\n"
        "Times elapsed: %" PRId64 "ms\n"
        "Data Rate: %.2Lf %s | %.2Lf %s | %.2Lf %s | %.2Lf %s\n",
        bytes_sent, bytes_sent / 1024.0L, bytes_sent / 1024.0L / 1024.0,
        elapsed_ms,
        data_rate_Bps, data_rate_unit_name(Bps),
        data_rate_convertf(data_rate_Bps, Bps, Gbps), data_rate_unit_name(Gbps),
        data_rate_convertf(data_rate_Bps, Bps, KiBps), data_rate_unit_name(KiBps),
        data_rate_convertf(data_rate_Bps, Bps, MiBps), data_rate_unit_name(MiBps)
    );

    return 0;
}

// References:
// https://nanomsg.org/gettingstarted/reqrep.html
