#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "../../../algorithm/misc/data_rate_unit.h"
#include "../../high_timer.h"
#include "../tcpip.h"


#define MAX_MSG_LEN (1024 * 128)


void start_client(socket_t sockfd, const _TCHAR *ipstr)
{
    char data[MAX_MSG_LEN] = { '\0' };
    int result;
    int total_bytes = 256 * 1024 * 1024;
    int turns = total_bytes / MAX_MSG_LEN;
    int64_t total_bytes_received = 0;
    high_timer_t timer;
    int64_t ellapsed_ms;
    long double data_rate_Bps;

    assert(sockfd != INVALID_SOCKET);

    high_timer_start(&timer);

    while (1)
    {
        result = recv(sockfd, data, MAX_MSG_LEN, 0);
        if (result == SOCKET_ERROR)
            break;

        if (data[0] == 'Q')
        {
            printf("Received 'Q' from server.\n");
            break;
        }

        total_bytes_received += result;

        turns -= 1;
        send(sockfd, turns == 0 ? "Q" : "Y", 1, 0);
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
}


// References:
// https://stackoverflow.com/questions/2844/how-do-you-printf-an-unsigned-long-long-intthe-format-specifier-for-unsigned-lo
// https://stackoverflow.com/questions/4089174/printf-and-long-double
// https://en.wikipedia.org/wiki/Data-rate_units
