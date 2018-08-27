#include "substr.h"

#include "stringview.h"


_TCHAR *substr(const _TCHAR *s, size_t pos, size_t count)
{
    return stringview_tostr(stringview_substr(s, pos, count));
}


const _TCHAR *substr_insitu(const _TCHAR *s, size_t pos, size_t count)
{
    return stringview_tostr_insitu(stringview_substr(s, pos, count));
}
