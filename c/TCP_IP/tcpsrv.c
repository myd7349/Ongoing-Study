// 2018-08-08T19:07+08:00
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_in_addr.h"


extern void start_server(socket_t sockfd);


#define DEFAULT_PORT _T("5678")


bool is_long(const _TCHAR *s, long *target)
{
    long value;
    _TCHAR *endptr;

    assert(s != NULL);

    value = _tcstol(s, &endptr, 0);
    if (errno == ERANGE || s == endptr || *endptr != _T('\0'))
        return false;

    if (target != NULL)
        *target = value;

    return true;
}


bool is_int(const _TCHAR *s, int *target)
{
    long value;
    bool res = is_long(s, &value);

    if (!res)
        return false;

#if LONG_MIN < INT_MIN || LONG_MAX > INT_MAX
    if (value < INT_MIN || value > INT_MAX)
        return false;
#endif

    if (target != NULL)
        *target = (int)value;

    return true;
}



typedef struct
{
    const _TCHAR *servname;
    int port;
    int backlog;
    int ipver;
} option_t;


bool parse_command_line_options(int argc, _TCHAR *argv[], option_t *options)
{
    int i;

    assert(options != NULL);

    if (argc > 7 || argc % 2 == 0) // argc should be: 1, 3, 5, 7
    {
        fprintf(stderr,
            "Usage:\n"
            "  tcpsrv [options]\n"
            "  tcpsrv [options]\n\n"
            "Options:\n"
            "  -port port\n"
            "  -backlog backlog\n"
            "  -ipver {0|4|6} - 0: AF_UNSPEC, 4: AF_INET, 6: AF_INET6\n"
        );
        return false;
    }

    options->servname = DEFAULT_PORT;
    options->backlog = SOMAXCONN;
    options->ipver = AF_UNSPEC;

    for (i = 1; i < argc; i += 2)
    {
        if (_tcscmp(argv[i], _T("-port")) == 0)
        {
            if (!is_int(argv[i + 1], &options->port) || options->port <= 0)
            {
                _ftprintf(stderr, _T("Invalid port number '%s'.\n"), argv[i + 1]);
                return false;
            }
            else
            {
                options->servname = argv[i + 1];
            }
        }
        else if (_tcscmp(argv[i], _T("-backlog")) == 0)
        {
            if (!is_int(argv[i + 1], &options->backlog) || options->backlog < 0)
            {
                _ftprintf(stderr, _T("Invalid backlog '%s'.\n"), argv[i + 1]);
                return false;
            }
        }
        else if (_tcscmp(argv[i], _T("-ipver")) == 0)
        {
            if (!is_int(argv[i + 1], &options->ipver) || 
                ((options->ipver != 0) && (options->ipver != 4) && (options->ipver != 6)))
            {
                _ftprintf(stderr, _T("Invalid IP version '%s'.\n"), argv[i + 1]);
                return false;
            }
            else
            {
                switch (options->ipver)
                {
                case 0: options->ipver = AF_UNSPEC; break;
                case 4: options->ipver = AF_INET; break;
                case 6:  options->ipver = AF_INET6; break;
                default: assert(false);  break;
                }
            }
        }
        else
        {
            _ftprintf(stderr, _T("Unknown option '%s'.\n"), argv[i]);
            return false;
        }
    }

    return true;
}


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

    start_server(sockfd);

    closesock(sockfd);
    return EXIT_SUCCESS;
}


// References:
// Beej's Guide to Network Programming Using Internet Sockets, Ch6.1
// https://stackoverflow.com/questions/22865622/atoi-vs-atol-vs-strtol-vs-strtoul-vs-sscanf
// Ongoing-study/cpp/CMake/encoding_test
