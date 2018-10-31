#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"
#include "../tcpip.h"


#define MAX_MSG_LEN (1024)
#define READY_MSG   "Pink Floyd: Time"


bool the_starting_gun(socket_t socket, struct sockaddr_storage *client_addr, socklen_t *sin_size)
{
    int result;
    char msg[256];

    *sin_size = sizeof(struct sockaddr_storage);
    result = recvfrom(socket, msg, strlen(READY_MSG) + 1, 0, (struct sockaddr *)client_addr, sin_size);
    if (result == SOCKET_ERROR)
    {
        print_error_ex(_T("recvfrom"));
        return false;
    }

    assert(result == strlen(READY_MSG) + 1);
    assert(strcmp(msg, READY_MSG) == 0);

    result = sendto(socket, READY_MSG, result, 0, (const struct sockaddr *)client_addr, *sin_size);
    if (result == SOCKET_ERROR)
    {
        print_error_ex(_T("sendto"));
        return false;
    }

    assert(result == strlen(READY_MSG) + 1);

    puts("Hey you! Do not help them to bury the light.");

    return true;
}


int start_udp_server(socket_t sockfd, const _TCHAR *endpoint)
{
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    int result;

    char msg;
    char data[MAX_MSG_LEN] = { '\0' };

    int64_t bytes_sent = 0;
    high_timer_t timer;
    int64_t ellapsed_ms;
    long double data_rate_Bps;

    assert(sockfd != INVALID_SOCKET);

    if (!the_starting_gun(sockfd, &client_addr, &sin_size))
        return EXIT_FAILURE;

    high_timer_start(&timer);

    while (true)
    {
        sin_size = sizeof(client_addr);
        result = recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, &sin_size);
        if (result == SOCKET_ERROR)
        {
            print_error_ex(_T("recvfrom"));
            break;
        }

        if (msg == 'Q')
        {
            puts("Received 'Q' from client.");
            data[0] = 'Q';
            sendto(sockfd, data, sizeof(data), 0, (const struct sockaddr *)&client_addr, sin_size);
            break;
        }
        else
        {
            result = sendto(sockfd, data, sizeof(data), 0, (const struct sockaddr *)&client_addr, sin_size);
            if (result == SOCKET_ERROR)
            {
                print_error_ex(_T("sendto"));
                break;
            }
            else
            {
                bytes_sent += result;
            }
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

    return EXIT_SUCCESS;
}
