#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../get_in_addr.h"

#define MAX_MSG_LEN 1024


int start_udp_server(socket_t sockfd, const _TCHAR *endpoint)
{
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    int result;

    _TCHAR ipstr[INET6_ADDRSTRLEN];

    _TCHAR msg[MAX_MSG_LEN];

    assert(sockfd != INVALID_SOCKET);
    
    sin_size = sizeof(client_addr);
    result = recvfrom(sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, &sin_size);
    if (result == SOCKET_ERROR)
    {
        print_error_ex(_T("recvfrom"));
        return EXIT_FAILURE;
    }

    if (inet_ntop(client_addr.ss_family,
        get_in_addr((struct sockaddr *)&client_addr),
        ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
        _ftprintf(stdout, _T("%s says: %s\n"), ipstr, msg);
    else
        fprintf(stderr, "inet_ntop failed.\n");

    return EXIT_SUCCESS;
}
