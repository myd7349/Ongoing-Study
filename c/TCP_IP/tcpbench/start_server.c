#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"
#include "../get_in_addr.h"
#include "../sendall.h"


#define MAX_MSG_LEN (1024 * 128)


int start_server(socket_t sockfd)
{
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    _TCHAR ipstr[INET6_ADDRSTRLEN];
    socket_t client_sockfd;
    char data[MAX_MSG_LEN] = { '\0' };
    char ack;
    int result;
    int64_t bytes_sent = 0;
    high_timer_t timer;
    int64_t elapsed_ms;
    long double data_rate_Bps;

    assert(sockfd != INVALID_SOCKET);

    sin_size = sizeof client_addr;
    client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
    if (client_sockfd == INVALID_SOCKET)
    {
        print_error_ex(_T("accept"));
        return EXIT_FAILURE;
    }

    if (inet_ntop(client_addr.ss_family,
        get_in_addr((struct sockaddr *)&client_addr),
        ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
    {
        _ftprintf(stdout, _T("Got connection from: %s.\n"), ipstr);
    }
    else
    {
        fprintf(stderr, "inet_ntop failed.\n");
    }

    high_timer_start(&timer);

    while (1)
    {
        result = sendall(client_sockfd, data, MAX_MSG_LEN);
        bytes_sent += result;
        if (result != MAX_MSG_LEN)
            break;

        result = recv(client_sockfd, &ack, 1, 0);
        if (result == SOCKET_ERROR)
            break;

        if (ack == 'Q')
        {
            printf("Received 'Q' from client.\n");
            send(client_sockfd, &ack, 1, 0);
            break;
        }
    }

    elapsed_ms = high_timer_elapsed_ms(&timer);
    data_rate_Bps = bytes_sent * 1000.0L / elapsed_ms;

    printf(
        "Total sent: %" PRId64 " bytes | %.2Lf KiB | %.2Lf MiB\n"
        "Times elapsed: %" PRId64 " ms\n"
        "Data Rate: %.2Lf %s | %.2Lf %s | %.2Lf %s | %.2Lf %s\n",
        bytes_sent, bytes_sent / 1024.0L, bytes_sent / 1024.0L / 1024.0,
        elapsed_ms,
        data_rate_Bps, data_rate_unit_name(Bps),
        data_rate_convertf(data_rate_Bps, Bps, Gbps), data_rate_unit_name(Gbps),
        data_rate_convertf(data_rate_Bps, Bps, KiBps), data_rate_unit_name(KiBps),
        data_rate_convertf(data_rate_Bps, Bps, MiBps), data_rate_unit_name(MiBps)
    );

    closesock(client_sockfd);

    return 0;
}


// References:
// Beej's Guide to Network Programming Using Internet Sockets, Ch7.3
// https://en.wikipedia.org/wiki/Data-rate_units
