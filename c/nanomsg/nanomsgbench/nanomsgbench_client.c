#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"
#include "../../TCP_IP/ipv4.h"


#define MAX_MSG_LEN (1024 * 128)
#define READY_MSG   ("Pink Floyd: Time")


#define FATAL_ERROR(func_name) \
    do \
    { \
        fprintf(stderr, "%s(%d): %s: %s\n", __FILE__, __LINE__, func_name, nn_strerror(nn_errno())); \
        exit(EXIT_FAILURE); \
    } while (0)


void wait_for_the_starting_gun(int socket)
{
    char msg[260];
    int bytes;

    if ((bytes = nn_send(socket, READY_MSG, strlen(READY_MSG) + 1, 0)) < 0)
        FATAL_ERROR("nn_send");

    if ((bytes = nn_recv(socket, msg, sizeof(msg), 0)) < 0)
        FATAL_ERROR("nn_recv");

    assert(bytes == strlen(READY_MSG) + 1);
    assert(strcmp(msg, READY_MSG) == 0);

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
    int64_t elapsed_ms;
    long double data_rate_Bps;
    high_timer_t timer;
    char remote_endpoint[260] = "";
    char msg[MAX_MSG_LEN];

    int socket;
    int result;

    if (argc == 1)
    {
        strcpy(remote_endpoint, "tcp://localhost:5678");
    }
    else if (argc == 2)
    {
        if (!ptohost(argv[1], NULL, true))
        {
            puts("Usage:\n  nanomsgbench_client <*.*.*.*:port>\n  (Example: nanomsgbench_client 127.0.0.1:5678)");
            return EXIT_FAILURE;
        }

        sprintf(remote_endpoint, "tcp://%s", argv[1]);
        printf("Remote endpoint: %s\n", remote_endpoint);
    }
    else
    {
        puts("Usage:\n  nanomsgbench_client <host:port>");
        return 1;
    }

    if ((socket = nn_socket(AF_SP, NN_REQ)) < 0)
        FATAL_ERROR("nn_socket");

    if ((result = nn_connect(socket, remote_endpoint)) < 0)
        FATAL_ERROR("nn_connect");

    wait_for_the_starting_gun(socket);

    high_timer_start(&timer);

    while (1)
    {
        if ((result = nn_send(socket, (turns-- == 0 ? "Q" : "Y"), 1, 0)) < 0)
            FATAL_ERROR("nn_send");

        if ((result = nn_recv(socket, msg, sizeof(msg), 0)) < 0)
            FATAL_ERROR("nn_recv");

        if (result == 1 && msg[0] == 'Q')
        {
            puts("Received 'Q' from server.");
            break;
        }
        else
        {
            total_bytes_received += result;
        }
    }

    nn_close(socket);

    elapsed_ms = high_timer_elapsed_ms(&timer);
    data_rate_Bps = total_bytes_received * 1000.0L / elapsed_ms;

    printf(
        "Total received: %" PRId64 " bytes | %.2Lf KiB | %.2Lf MiB\n"
        "Times elapsed: %" PRId64 " ms\n"
        "Data Rate: %.2Lf %s | %.2Lf %s | %.2Lf %s | %.2Lf %s\n",
        total_bytes_received, total_bytes_received / 1024.0L, total_bytes_received / 1024.0L / 1024.0,
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
// https://github.com/goldsborough/ipc-bench
