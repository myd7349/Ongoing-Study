#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"
#include "../tcpip.h"

#define MAX_MSG_LEN (1024)
#define READY_MSG   ("Pink Floyd: Time")


bool wait_for_the_starting_gun(socket_t socket, bool connected, addrinfo_t *addr)
{
    char msg[260];
    int result;

    assert(socket != INVALID_SOCKET);

    result = connected ?
        send(socket, READY_MSG, strlen(READY_MSG) + 1, 0) :
        sendto(socket, READY_MSG, strlen(READY_MSG) + 1, 0, addr->ai_addr, addr->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        if (connected)
            print_error_ex(_T("send"));
        else
            print_error_ex(_T("sendto"));
        return false;
    }

    assert(result == strlen(READY_MSG) + 1);

    result = connected ?
        recv(socket, msg, result, 0) :
        recvfrom(socket, msg, result, 0, addr->ai_addr, &addr->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        if (connected)
            print_error_ex(_T("recv"));
        else
            print_error_ex(_T("recvfrom"));
        return false;
    }

    assert(result == strlen(READY_MSG) + 1);
    assert(strcmp(msg, READY_MSG) == 0);

    puts(
        "And you run and you run to catch up with the sun, but it's sinking\n"
        "And racing around to come up behind you again\n"
        "The sun is the same in the relative way, but you're older\n"
        "Shorter of breath and one day closer to death"
    );

    return true;
}


int start_udp_client(socket_t sockfd, const _TCHAR *endpoint, bool connected, addrinfo_t *addr)
{
    int result;

    char data[MAX_MSG_LEN] = { '\0' };

    int total_bytes = 256 * 1024 * 1024;
    int turns = total_bytes / MAX_MSG_LEN;
    int64_t total_bytes_received = 0;
    int64_t ellapsed_ms;
    long double data_rate_Bps;
    high_timer_t timer;

    assert(sockfd != INVALID_SOCKET);
    assert(addr != NULL || connected);

    if (!wait_for_the_starting_gun(sockfd, connected, addr))
        return EXIT_FAILURE;

    high_timer_start(&timer);

    while (true)
    {
        char msg = turns-- == 0 ? 'Q' : 'Y';
        result = connected ?
            send(sockfd, &msg, 1, 0) :
            sendto(sockfd, &msg, 1, 0, addr->ai_addr, addr->ai_addrlen);
        if (result == SOCKET_ERROR)
        {
            print_error_ex(_T("sendto"));
            break;
        }

        result = connected ?
            recv(sockfd, data, sizeof(data), 0) :
            recvfrom(sockfd, data, sizeof(data), 0, (struct sockaddr *)addr->ai_addr, &addr->ai_addrlen);
        if (result == SOCKET_ERROR)
        {
            print_error_ex(_T("recvfrom"));
            break;
        }

        assert(result == sizeof(data));
        if (data[0] == 'Q')
        {
            puts("Received 'Q' from server.");
            break;
        }
        else
        {
            total_bytes_received += result;
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

    return EXIT_SUCCESS;
}
