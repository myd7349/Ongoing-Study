#include <assert.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../ttoi.h"
#include "../get_in_addr.h"

#include <getopt.h>


#define MSG_MAX_LEN 1024


typedef struct
{
    const _TCHAR *host;
    const _TCHAR *serv;
    int           ipver;
} client_option_t;


bool parse_options(int argc, _TCHAR *argv[], client_option_t *options)
{
    const char *usage =
        "Usage:\n"
        "  tcpclient <options>\n\n"
        "Options:\n"
        "  --host,-H   Specify host name\n"
        "  --serv,-S   Specify service name\n"
        "  --ipver,-I  Specify IP version {0|4|6}\n"
        "  --help,-h   Show help message";

    struct option long_options[] =
    {
        { _T("host"), required_argument, NULL, _T('H') },
        { _T("serv"), required_argument, NULL, _T('S') },
        { _T("ipver"), required_argument, NULL, _T('I') },
        { _T("help"), no_argument, NULL, _T('h') },
        { NULL, 0, NULL, 0 }
    };

    int c;
    int option_index;
    bool ok;

    assert(options != NULL);

    options->host = options->serv = NULL;
    options->ipver = AF_UNSPEC;

    while ((c = getopt_long(argc, argv, _T("H:S:I:h"), long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case _T('H'):
            options->host = optarg;
            break;
        case _T('S'):
            options->serv = optarg;
            break;
        case _T('I'):
            options->ipver = ttoi(optarg, &ok);
            if (!ok || options->ipver != 0 && options->ipver != 4 && options->ipver != 6)
            {
                _ftprintf(stderr, _T("Invalid IP version number: '%s'.\n"), optarg);
                return false;
            }

            switch (options->ipver)
            {
            case 0: options->ipver = AF_UNSPEC; break;
            case 4: options->ipver = AF_INET; break;
            case 6: options->ipver = AF_INET6; break;
            }
            break;
        case _T('h'):
            puts(usage);
            return false;
            break;
        case '?':
            return false;
            break;
        default:
            fprintf(stderr, "?? getopt_long returned character code 0%o ??\n", c);
            return false;
            break;
        }
    }

    if (options->host == NULL && options->serv == NULL)
    {
        fprintf(stderr, "At least one of '--host', '--serv' should be specified.\n");
        return false;
    }

    return true;
}


extern void start_client(socket_t sockfd, const _TCHAR *ipstr);


int _tmain(int argc, _TCHAR *argv[])
{
    client_option_t options;

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
            _ftprintf(stdout, _T("Client is running on %s:%s.\n"), ipstr, options.serv);
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
