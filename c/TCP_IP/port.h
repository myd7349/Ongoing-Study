#ifndef PORT_H_
#define PORT_H_

#include <stdbool.h>
#include <stdint.h>

#include "../common.h"
#include "../tchardef.h"


C_API_BEGIN

bool is_valid_port_number(const _TCHAR *str, uint16_t *port);

C_API_END

#endif // PORT_H_
