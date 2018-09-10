#include <locale.h>
#include <stdlib.h>

#include "../../clog.h"
#include "../../common.h"
#include "../../getprogname.h"
#include "../ipv4.h"
#include "../tcpip.h"


int _tmain(int argc, _TCHAR *argv[])
{
    int af;
    int result;
    unsigned char buf[sizeof(struct in6_addr)];
    _TCHAR addr[INET6_ADDRSTRLEN];

    if (argc != 2)
    {
        _TCHAR *prog = getprogname(argv[0]);
        _ftprintf(stdout, _T("Usage:\n  %s <host>\n"), prog);
        free(prog);

        return EXIT_FAILURE;
    }

    TCP_IP_INIT();

    af = ptohost(argv[1], NULL, false) ? AF_INET : AF_INET6;
    result = inet_pton(af, argv[1], buf);
    
    if (result != 1)
    {
        if (result == 0)
            ERR("Invalid IPv4/Ipv6 address.\n");
        else if (result == -1)
            print_error_ex(_T("inet_pton"));
        else
            ERR("Unexpected return value: %d.\n", result);

        return EXIT_FAILURE;
    }

    if (inet_ntop(af, buf, addr, ARRAYSIZE(addr)) == NULL)
    {
        print_error_ex(_T("inet_ntop"));
        return EXIT_FAILURE;
    }

    _tprintf(_T("%s\n"), addr);

    return 0;
}


// References:
// http://man7.org/linux/man-pages/man3/inet_pton.3.html
// https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class
