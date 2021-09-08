// 2018-08-08T19:07+08:00
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_in_addr.h"
#include "tcpopt.h"


extern int start_server(socket_t sockfd);


int _tmain(int argc, _TCHAR *argv[])
{
    option_t options;
    int result;
    int yes = 1;

    addrinfo_t hints;
    addrinfo_t *ailist = NULL, *aiptr = NULL;

    socket_t sockfd = INVALID_SOCKET;

    _TCHAR ipstr[INET6_ADDRSTRLEN];

#ifdef WIN32
    _tsetlocale(LC_ALL, _T(""));
#endif

    if (!parse_command_line_options(argc, argv, &options))
        return EXIT_FAILURE;

    TCP_IP_INIT();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = options.ipver;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, options.servname, &hints, &ailist);
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

#ifdef WIN32
        result = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));
#else
        result = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
#endif
        if (result != 0) // result == -1
        {
            print_error_ex(_T("setsockopt"));
            freeaddrinfo(ailist);
            return EXIT_FAILURE;
        }

        result = bind(sockfd, aiptr->ai_addr, aiptr->ai_addrlen);
        if (result != 0)
        {
            closesock(sockfd);
            print_error_ex(_T("bind"));
        }
        else
        {
            break;
        }
    }

    if (aiptr == NULL)
    {
        freeaddrinfo(ailist);
        _ftprintf(stderr, _T("Failed to bind to %s.\n"), options.servname);
        return EXIT_FAILURE;
    }
    else
    {
        if (inet_ntop(aiptr->ai_family, get_in_addr(aiptr->ai_addr),
            ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
        {
            _ftprintf(stdout, _T("Server is running on %s:%s.\n"), ipstr, options.servname);
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

    result = listen(sockfd, options.backlog);
    if (result != 0)
    {
        closesock(sockfd);
        print_error_ex(_T("listen"));
        return EXIT_FAILURE;
    }

    result = start_server(sockfd);

    closesock(sockfd);
    return result;
}


// References:
// Beej's Guide to Network Programming Using Internet Sockets, Ch6.1
// Ongoing-study/cpp/CMake/encoding_test
// https://github.com/TheAlgorithms/C/blob/master/client_server/tcp_full_duplex_server.c
