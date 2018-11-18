#include "stringview.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h> // SIZE_MAX
#include <stdlib.h>
#include <string.h>


#define VALIDATE_STRINGVIEW(s) \
    assert(s.cbegin != NULL && (s.count >= 0) || s.cbegin == NULL && s.count == 0)


stringview_t stringview_substr(const _TCHAR *s, size_t pos, size_t count)
{
    stringview_t view = { NULL, 0 };
    size_t len;

    assert(s != NULL);
    assert(pos != stringview_npos);

    if (count == 0)
        return view;

    len = _tcslen(s);
    assert(pos <= len);

    if (pos > len)
    {
        errno = EINVAL;
        return view;
    }
    else if (len >= SIZE_MAX - 1)
    {
        errno = ERANGE;
        return view;
    }

    if (count == stringview_npos || count > len - pos)
        count = len - pos;

    view.cbegin = s + pos;
    view.count = count;
    return view;
}


size_t stringview_length(stringview_t view)
{
    VALIDATE_STRINGVIEW(view);
    return view.count;
}


_TCHAR *stringview_tostr(stringview_t view)
{
    _TCHAR *s = NULL;
    size_t size;

    VALIDATE_STRINGVIEW(view);
    if (view.cbegin == NULL)
        return NULL;

    size = view.count + 1;
    s = malloc(size * sizeof(_TCHAR));
    if (s == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }

    _tcsncpy(s, view.cbegin, size);
    s[view.count] = _T('\0');
    return s;
}


const _TCHAR *stringview_tostr_insitu(stringview_t view)
{
    VALIDATE_STRINGVIEW(view);
    if (view.cbegin == NULL)
        return NULL;

    if (view.cbegin[view.count] == _T('\0'))
        return view.cbegin;
    else
        return NULL;
}


// References:
// http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html
// cppreference:strncpy
