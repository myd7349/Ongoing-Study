#ifndef GET_PROG_NAME_H_
#define GET_PROG_NAME_H_

#include "common.h"
#include "tchardef.h"

C_API_BEGIN

_TCHAR *getprogname(const _TCHAR *argv0);

C_API_END

#endif // GET_PROG_NAME_H_
