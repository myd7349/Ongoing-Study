#include "ipv4.h"

#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>


bool ptohost(const _TCHAR *str, ipv4_host_t *host, bool needs_port_number)
{
    uint16_t ip_addr[4] = { 260, 260, 260, 260 };
    uint32_t port = 65537;

    assert(str != NULL);


    //_stscanf(str, _T("%hu%*[^.].%hu%*[^.].%hu%*[^.].%hu%*[^:]:%u"),
    _stscanf(str,
        _T("%") _T(PRIu16) _T(" . ")
        _T("%") _T(PRIu16) _T(" . ")
        _T("%") _T(PRIu16) _T(" . ")
        _T("%") _T(PRIu16)
        _T(" : ")
        _T("%") _T(PRIu32),
        ip_addr + 0, ip_addr + 1, ip_addr + 2, ip_addr + 3, &port);

    if (ip_addr[0] == 260 || ip_addr[1] == 260 || ip_addr[2] == 260 || ip_addr[3] == 260)
        return false;

    if (needs_port_number && port > USHRT_MAX)
        return false;

    if (host != NULL)
    {
        host->ip[0] = (uint8_t)ip_addr[0];
        host->ip[1] = (uint8_t)ip_addr[1];
        host->ip[2] = (uint8_t)ip_addr[2];
        host->ip[3] = (uint8_t)ip_addr[3];
        host->has_port_number = port <= USHRT_MAX;
        host->port = host->has_port_number ? (uint16_t)port : (uint16_t)0;
    }

    return true;
}


bool hosttop(ipv4_host_t *host, _TCHAR *str, size_t count)
{
    return false;
}


// References:
// https://www.cnblogs.com/fullsail/p/4285215.html
