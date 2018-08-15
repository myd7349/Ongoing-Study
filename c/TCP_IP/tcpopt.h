#ifndef TCPOPT_H_
#define TCPOPT_H_

#include <stdbool.h>

#include "tcpip.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define DEFAULT_PORT _T("5678")

typedef struct
{
    const _TCHAR *servname;
    int port;
    int backlog;
    int ipver;
} option_t;

bool parse_command_line_options(int argc, _TCHAR *argv[], option_t *options);

#ifdef __cplusplus
}
#endif

#endif // TCPOPT_H_
