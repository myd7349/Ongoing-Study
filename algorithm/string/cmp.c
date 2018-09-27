#include "cmp.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>


int cmp(const _TCHAR *s1, const _TCHAR *s2)
{
    return ncmp(s1, s2, _tcslen(s2));
}


int ncmp(const _TCHAR *s1, const _TCHAR *s2, size_t count)
{
    size_t i;
    int result;

    assert(s1 != NULL);
    assert(s2 != NULL);

    for (i = 0; i < count; ++i)
    {
        if (*s1 == _T('\0') && *s2 == _T('\0'))
            return 0;

        if ((result = *s1 - *s2) != 0)
            return result > 0 ? 1 : -1;

        s1++;
        s2++;
    }

    return 0;
}


int icmp(const _TCHAR *s1, const _TCHAR *s2)
{
    return nicmp(s1, s2, _tcslen(s2));
}


int nicmp(const _TCHAR *s1, const _TCHAR *s2, size_t count)
{
    size_t i;
    int result;

    assert(s1 != NULL);
    assert(s2 != NULL);

    for (i = 0; i < count; ++i)
    {
        if (*s1 == _T('\0') && *s2 == _T('\0'))
            return 0;

        if ((result = tolower(*s1) - tolower(*s2)) != 0)
            return result > 0 ? 1 : -1;

        s1++;
        s2++;
    }

    return 0;
}

// nanomsg-1.1.4/src/utils/strncasecmp.c
// MSVC: stricmp, strnicmp
// linux <strings.h>: strcasecmp, strncasecmp
// https://linux.die.net/man/3/strcasecmp
