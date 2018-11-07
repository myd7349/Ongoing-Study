#include <inttypes.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../getprogname.h"
#include "../port.h"
#include "../tcpip.h"

#define DEFAULT_PORT_NUMBER 5678


int _tmain(int argc, _TCHAR *argv[])
{
    _TCHAR *host = NULL;
    uint16_t port = DEFAULT_PORT_NUMBER;
    const _TCHAR *msg = NULL;

    struct sockaddr_in their_addr;
    struct hostent *he;

    socket_t sockfd;

    int nbytes;

    _TCHAR *progname;

#if defined(_WIN32)
    char broadcast = '1';
#elif defined(__linux__)
    int broadcast = 1;
#else
# error Not tested yet!
#endif

#if defined(_WIN32) && defined(_UNICODE)
    _tsetlocale(LC_ALL, _T(""));
#endif

    if (argc != 3 && argc != 4)
    {
        progname = getprogname(argv[0]);
        _ftprintf(stderr, _T("Usage:\n  %s <host> [port] <message>"), progname);
        free(progname);
        return EXIT_FAILURE;
    }

    host = argv[1];
    msg = argv[2];

    if (argc == 4)
    {
        if (!is_valid_port_number(argv[2], &port))
        {
            _ftprintf(stderr, _T("Invalid port number: %s\n"), argv[2]);
            return EXIT_FAILURE;
        }

        msg = argv[3];
    }

    TCP_IP_INIT();

    if ((he = gethostbyname(host)) == NULL)
    {
        print_error_ex(_T("gethostbyname"));
        return EXIT_FAILURE;
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        print_error_ex(_T("socket"));
        return EXIT_FAILURE;
    }

#if defined(_WIN32)
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == SOCKET_ERROR)
#elif defined(__linux__)
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == SOCKET_ERROR)
#endif
    {
        print_error_ex(_T("setsockopt(SO_BROADCAST)"));
        closesock(sockfd);
        return EXIT_FAILURE;
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(port);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, 0, sizeof their_addr.sin_zero);

    nbytes = sendto(sockfd, (const char *)msg, (_tcslen(msg) + 1) * sizeof(_TCHAR), 0,
        (const struct sockaddr *)&their_addr, sizeof their_addr);
    if (nbytes == SOCKET_ERROR)
        print_error_ex(_T("sendto"));
    else
        _tprintf(_T("Sent %d bytes to %s:%") _T(PRIu16) _T(".\n"), nbytes, inet_ntoa(their_addr.sin_addr), port);

    closesock(sockfd);

    return 0;
}
