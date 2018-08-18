#include "ttoi.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>


long ttol(const _TCHAR *s, bool *ok)
{
    long value;
    _TCHAR *endptr;

    assert(s != NULL);
    assert(ok != NULL);

    value = _tcstol(s, &endptr, 0);
    if (errno == ERANGE || s == endptr || *endptr != _T('\0'))
    {
        *ok = false;
        return 0;
    }
    else
    {
        *ok = true;
        return value;
    }
}


int ttoi(const _TCHAR *s, bool *ok)
{
    long value = ttol(s, ok);
    if (!ok)
        return 0;

#if LONG_MIN < INT_MIN || LONG_MAX > INT_MAX
    if (value < INT_MIN || value > INT_MAX)
    {
        *ok = false;
        return 0;
    }
#endif

    return (int)value;
}
