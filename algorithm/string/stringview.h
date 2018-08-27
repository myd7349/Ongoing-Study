#ifndef STRING_VIEW_H_
#define STRING_VIEW_H_

#include <stddef.h>

#include "../../c/common.h"
#include "../../c/tchardef.h"


C_API_BEGIN

#define stringview_npos ((size_t)(~0))

typedef struct
{
    const _TCHAR *cbegin;
    size_t        count;
} stringview_t;

stringview_t stringview_substr(const _TCHAR *s, size_t pos, size_t count);
size_t stringview_length(stringview_t s);
_TCHAR *stringview_tostr(stringview_t s);
const _TCHAR *stringview_tostr_insitu(stringview_t s);

C_API_END

#endif // STRING_VIEW_H_
