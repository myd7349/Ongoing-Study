#include <assert.h>
#include <locale.h>
#include <stdlib.h>

#include "get_in_addr.h"
#include "options.h"


int start_udp_client(socket_t sockfd, const _TCHAR *ipstr, bool connected, addrinfo_t *addr);


int _tmain(int argc, _TCHAR *argv[])
{
    option_ex_t options;

    addrinfo_t hints;
    addrinfo_t *ailist = NULL, *aiptr = NULL;
    int result;

    socket_t sockfd = INVALID_SOCKET;

    _TCHAR ipstr[INET6_ADDRSTRLEN];

    bool connected = false;

#ifdef _WIN32
    _tsetlocale(LC_ALL, _T(""));
#endif

    if (!parse_options_ex(argc, argv, &options))
        return EXIT_FAILURE;

    TCP_IP_INIT();

    if (options.bind)
    {
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = options.ipver;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;

        result = getaddrinfo(options.local_host, options.local_serv, &hints, &ailist);
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
            _ftprintf(stderr, _T("Failed to bind to %s.\n"), options.local_serv);
            return EXIT_FAILURE;
        }
        else
        {
            if (inet_ntop(aiptr->ai_family, get_in_addr(aiptr->ai_addr),
                ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
            {
                _ftprintf(stdout, _T("Client is running on %s:%s.\n"), ipstr, options.local_serv);
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
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = options.ipver;
    hints.ai_socktype = SOCK_DGRAM;

    result = getaddrinfo(options.remote_host, options.remote_serv, &hints, &ailist);
    if (result != 0)
    {
        print_error_ex(_T("getaddrinfo"));
        return EXIT_FAILURE;
    }

    for (aiptr = ailist; aiptr != NULL; aiptr = aiptr->ai_next)
    {
        if (sockfd == INVALID_SOCKET)
        {
            sockfd = socket(aiptr->ai_family, aiptr->ai_socktype, aiptr->ai_protocol);
            if (sockfd == INVALID_SOCKET)
            {
                print_error_ex(_T("socket"));
                continue;
            }
        }

        if (options.connect)
        {
            result = connect(sockfd, aiptr->ai_addr, aiptr->ai_addrlen);
            if (result != 0)
            {
                print_error_ex(_T("connect"));
                continue;
            }
            else
            {
                connected = true;
            }
        }

        break;
    }

    if (connected)
    {
        if (inet_ntop(aiptr->ai_family, get_in_addr(aiptr->ai_addr),
            ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
        {
            _ftprintf(stdout, _T("Client is connected to %s:%s.\n"), ipstr, options.remote_serv);
        }
        else
        {
            freeaddrinfo(ailist);
            fprintf(stderr, "inet_ntop failed.\n");
            return EXIT_FAILURE;
        }
    }

    result = start_udp_client(sockfd, ipstr, connected, aiptr);

    freeaddrinfo(ailist);
    ailist = NULL;
    aiptr = NULL;

    closesock(sockfd);

    return result;
}

// References:
// https://github.com/beejjorgensen/bgnet/blob/master/examples/talker.c
// https://github.com/TheAlgorithms/C/blob/master/client_server/udp_client.c
