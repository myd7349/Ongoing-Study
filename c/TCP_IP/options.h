#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <stdbool.h>

#include "../common.h"
#include "../tchardef.h"


C_API_BEGIN

typedef struct
{
    const _TCHAR *host;
    const _TCHAR *serv;
    int           ipver;
} option_t;


typedef struct
{
    const _TCHAR *local_host;
    const _TCHAR *local_serv;
    const _TCHAR *remote_host;
    const _TCHAR *remote_serv;
    int           ipver;
    bool          bind;
    bool          connect;
} option_ex_t;

bool parse_options(int argc, _TCHAR *argv[], option_t *options);

bool parse_options_ex(int argc, _TCHAR *argv[], option_ex_t *options);

C_API_END

#endif // OPTIONS_H_
