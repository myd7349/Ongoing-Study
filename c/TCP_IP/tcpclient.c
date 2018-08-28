#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_in_addr.h"
#include "options.h"


#define MSG_MAX_LEN 1024


extern void start_client(socket_t sockfd, const _TCHAR *ipstr);


int _tmain(int argc, _TCHAR *argv[])
{
    option_t options;

    addrinfo_t hints;
    addrinfo_t *ailist = NULL, *aiptr = NULL;

    socket_t sockfd = INVALID_SOCKET;

    _TCHAR ipstr[INET6_ADDRSTRLEN];

    int result;

#ifdef WIN32
    _tsetlocale(LC_ALL, _T(""));
#endif

    if (!parse_options(argc, argv, &options))
        return EXIT_FAILURE;

    TCP_IP_INIT();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = options.ipver;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(options.host, options.serv, &hints, &ailist);
    if (result != 0)
    {
        print_error_ex(_T("getaddrinfo"));
        return EXIT_FAILURE;
    }

    for (aiptr = ailist; aiptr != NULL; aiptr = aiptr->ai_next)
    {
        sockfd = socket(aiptr->ai_family, aiptr->ai_socktype, aiptr->ai_protocol);
        if (sockfd == INVALID_SOCKET)
        {
            print_error_ex(_T("socket"));
            continue;
        }

        result = connect(sockfd, aiptr->ai_addr, aiptr->ai_addrlen);
        if (result != 0)
        {
            closesock(sockfd);
            print_error_ex(_T("connect"));
        }
        else
        {
            break;
        }
    }

    if (aiptr == NULL)
    {
        freeaddrinfo(ailist);
        _ftprintf(stderr, _T("Failed to connect to %s:%s.\n"), options.host, options.serv);
        return EXIT_FAILURE;
    }
    else
    {
        if (inet_ntop(aiptr->ai_family, get_in_addr(aiptr->ai_addr),
            ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
        {
            _ftprintf(stdout, _T("Client connected to %s:%s.\n"), ipstr, options.serv);
        }
        else
        {
            freeaddrinfo(ailist);
            fprintf(stderr, "inet_ntop failed.\n");
            return EXIT_FAILURE;
        }
    }

    freeaddrinfo(ailist);
    ailist = NULL;
    aiptr = NULL;

    start_client(sockfd, ipstr);

    closesock(sockfd);
    return EXIT_SUCCESS;
}


// References:
// Beej's Guide to Network Programming Using Internet Sockets, Ch6.2
// https://www.gnu.org/software/libc/manual/html_node/Getopt.html
