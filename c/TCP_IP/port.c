#include "port.h"

#include <assert.h>
#include <limits.h>

#include "../ttoi.h"


bool is_valid_port_number(const _TCHAR *str, uint16_t *port)
{
    bool ok;
    long number = ttol(str, &ok);
    if (!ok)
        return false;

    if (number > USHRT_MAX)
        return false;

    if (port != NULL)
        *port = (uint16_t)number;
    return true;
}
