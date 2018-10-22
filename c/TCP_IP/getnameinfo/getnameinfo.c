#include <inttypes.h>
#include <stdlib.h>

#include "../../clog.h"
#include "../../common.h"
#include "../../getprogname.h"
#include "../get_in_addr.h"
#include "../ipv4.h"



int _tmain(int argc, _TCHAR *argv[])
{
    struct sockaddr_storage addr = { 0 };
    ipv4_host_t ipv4_host;
    int result;
    socklen_t addrlen;
    _TCHAR host[NI_MAXHOST];
    _TCHAR serv[NI_MAXSERV];

    if (argc != 2)
    {
        _TCHAR *prog = getprogname(argv[0]);
        _ftprintf(stdout, _T("Usage:\n  %s <host>\n"), prog);
        free(prog);

        return EXIT_FAILURE;
    }

    TCP_IP_INIT();

    addr.ss_family = ptohost(argv[1], &ipv4_host, false) ? AF_INET : AF_INET6;
    if (addr.ss_family == AF_INET)
    {
        if (ipv4_host.has_port_number)
        {
            _TCHAR ipv4_addr[INET_ADDRSTRLEN];
            _sntprintf(ipv4_addr, sizeof(ipv4_addr) / sizeof(ipv4_addr[0]),
                _T("%") _T(PRIu16) _T(".")
                _T("%") _T(PRIu16) _T(".")
                _T("%") _T(PRIu16) _T(".")
                _T("%") _T(PRIu16),
                ipv4_host.ip[0],
                ipv4_host.ip[1],
                ipv4_host.ip[2],
                ipv4_host.ip[3]);

            result = inet_pton(addr.ss_family, ipv4_addr, &((struct sockaddr_in *)&addr)->sin_addr);
            ((struct sockaddr_in *)&addr)->sin_port = htons(ipv4_host.port);
        }
        else
        {
            result = inet_pton(addr.ss_family, argv[1], &((struct sockaddr_in *)&addr)->sin_addr);
        }
    }
    else
    {
        // [2000:0000:0000:0000:0001:2345:6789:abcd]:5060
        _TCHAR *port_prefix_pos = _tcsstr(argv[1], _T("]:"));
        if (argv[1][0] == _T('[') && port_prefix_pos != NULL)
        {
            _TCHAR ipv6_addr[INET6_ADDRSTRLEN] = { _T('\0') };
            long port = _tcstol(port_prefix_pos + 2, NULL, 0);
            if (port >= USHRT_MAX)
            {
                ERR("Invalid IPv4/Ipv6 address.\n");
                return EXIT_FAILURE;
            }

            // strncpy: a null character may not be appended.
            _tcsncpy(ipv6_addr, argv[1] + 1, port_prefix_pos - argv[1] - 1);

            result = inet_pton(addr.ss_family, ipv6_addr, &((struct sockaddr_in6 *)&addr)->sin6_addr);
            ((struct sockaddr_in6 *)&addr)->sin6_port = htons((uint16_t)port);
        }
        else
        {
            result = inet_pton(addr.ss_family, argv[1], &((struct sockaddr_in6 *)&addr)->sin6_addr);
        }
    }
    
    if (result != 1)
    {
        if (result == 0)
        {
            ERR("Invalid IPv4/Ipv6 address.\n");
            return EXIT_FAILURE;
        }
        else if (result == -1)
        {
            print_error_ex(_T("inet_pton"));
            return EXIT_FAILURE;
        }
        else
        {
            ERR("Unexpected return value: %d.\n", result);
            return EXIT_FAILURE;
        }
    }

    addrlen = addr.ss_family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

    result = getnameinfo((const struct sockaddr *)&addr,
        addrlen, host, ARRAYSIZE(host), serv, ARRAYSIZE(serv), NI_NUMERICHOST | NI_NUMERICSERV);
    if (result != 0)
    {
        ERR("getnameinfo failed(%d): ", result);
        print_error(_T("getnameinfo"), result);
        return result;
    }

    _tprintf(_T("Host: %s\nServ: %s\n"), host, serv);

    return 0;
}


// References:
// https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class
// http://man7.org/linux/man-pages/man3/getnameinfo.3.html
// http://man7.org/linux/man-pages/man3/inet_pton.3.html
// https://docs.microsoft.com/en-us/windows/desktop/api/ws2tcpip/nf-ws2tcpip-inetptonw
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms740504(v=vs.85).aspx
