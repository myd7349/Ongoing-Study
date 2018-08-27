#ifndef SUBSTR_H_
#define SUBSTR_H_

#include <stddef.h>

#include "../../c/common.h"
#include "../../c/tchardef.h"


C_API_BEGIN

#define str_npos ((size_t)(~0))

_TCHAR *substr(const _TCHAR *s, size_t pos, size_t count);
const _TCHAR *substr_insitu(const _TCHAR *s, size_t pos, size_t count);

C_API_END

#endif // SUBSTR_H_
