#include "options.h"

#include <stdio.h>

#include <getopt.h>

#include "../getprogname.h"
#include "../ttoi.h"
#include "tcpip.h"


#define DEFAULT_PORT _T("5678")


bool parse_options(int argc, _TCHAR *argv[], option_t *options)
{
    const _TCHAR *usage =
        _T("Usage:\n")
        _T("  %s <options>\n\n")
        _T("Options:\n")
        _T("  --host,-H   Specify host name\n")
        _T("  --serv,-S   Specify service name\n")
        _T("  --ipver,-I  Specify IP version {0|4|6}\n")
        _T("  --help,-h   Show help message\n");

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

    assert(argc >= 1);
    assert(argv != NULL);
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
        {
            _TCHAR *progname = getprogname(argv[0]);
            _ftprintf(stderr, usage, progname != NULL ? progname : argv[0]);
            if (progname != NULL)
                free(progname);
            return false;
        }
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

    if (options->serv == NULL)
        options->serv = DEFAULT_PORT;

    return true;
}


bool parse_options_ex(int argc, _TCHAR *argv[], option_ex_t *options)
{
    const _TCHAR *usage =
        _T("Usage:\n")
        _T("  %s <options>\n\n")
        _T("Options:\n")
        _T("  --local-host   <host>   Specify local host name\n")
        _T("  --local-serv   <serv>   Specify local service name\n")
        _T("  --remote-host  <host>   Specify remote host name\n")
        _T("  --remote-serv  <serv>   Specify remote service name\n")
        _T("  --ipver        <ipver>  Specify IP version: {0|4|6}\n")
        _T("  --bind                  Bind to local host\n")
        _T("  --connect               Connect to remote host\n")
        _T("  --help,-h               Show help message\n");

    _TCHAR *progname = NULL;

    struct option long_options[] =
    {
        { _T("local-host"), required_argument, NULL, 0 },
        { _T("local-serv"), required_argument, NULL, 1 },
        { _T("remote-host"), required_argument, NULL, 2 },
        { _T("remote-serv"), required_argument, NULL, 3 },
        { _T("ipver"), required_argument, NULL, 4 },
        { _T("bind"), no_argument, NULL, 5 },
        { _T("connect"), no_argument, NULL, 6 },
        { _T("help"), no_argument, NULL, _T('h') },
        { NULL, 0, NULL, 0 }
    };

    int c;
    int option_index;
    int ipver;
    bool ok;

    assert(argc >= 1);
    assert(argv != NULL);
    assert(options != NULL);

    options->local_host = options->local_serv = NULL;
    options->remote_host = options->remote_serv = NULL;
    options->ipver = AF_UNSPEC;
    options->bind = false;
    options->connect = false;

    while ((c = getopt_long(argc, argv, _T("h"), long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case '?': return false; break;
        case 'h':
            progname = getprogname(argv[0]);
            _ftprintf(stderr, usage, progname != NULL ? progname : argv[0]);
            free(progname);
            return false;
            break;
        default: break;
        }

        switch (option_index)
        {
        case 0: options->local_host = optarg; break;
        case 1: options->local_serv = optarg; break;
        case 2: options->remote_host = optarg; break;
        case 3: options->remote_serv = optarg; break;
        case 4:
            ipver = ttoi(optarg, &ok);
            if (!ok || ipver != 0 && ipver != 4 && ipver != 6)
            {
                _ftprintf(stderr, _T("Invalid IP version number: '%s'.\n"), optarg);
                return false;
            }

            switch (ipver)
            {
            case 0: ipver = AF_UNSPEC; break;
            case 4: ipver = AF_INET; break;
            case 6: ipver = AF_INET6; break;
            }

            options->ipver = ipver;
            break;
        case 5: options->bind = true; break;
        case 6: options->connect = true; break;
        default:
            break;
        }
    }

    if (options->local_serv == NULL)
        options->local_serv = DEFAULT_PORT;

    if (options->remote_serv == NULL)
        options->remote_serv = DEFAULT_PORT;

    return true;
}
