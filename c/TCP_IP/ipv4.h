#ifndef IS_IPV4_H_
#define IS_IPV4_H_

#include <stdbool.h>
#include <stdint.h>

#include "../common.h"
#include "../tchardef.h"


C_API_BEGIN

typedef struct
{
    uint8_t  ip[4];
    uint16_t port;
    bool     has_port_number;
} ipv4_host_t;

bool ptohost(const _TCHAR *str, ipv4_host_t *host, bool needs_port_number);
bool hosttop(ipv4_host_t *host, _TCHAR *str, size_t count);

C_API_END

#endif // IS_IPV4_H_
