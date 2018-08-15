#include "tcpopt.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>


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
    is_int(DEFAULT_PORT, &options->port);
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
