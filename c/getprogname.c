#include "getprogname.h"

#include <string.h>

#include "../algorithm/string/substr.h"


// Get file name without extension
_TCHAR *getprogname(const _TCHAR *argv0)
{
    _TCHAR *last_pathsep_pos = NULL;
    _TCHAR *last_dot_pos = NULL;
    size_t pos = 0;
    size_t count = str_npos;

    assert(argv0 != NULL);

    last_pathsep_pos = _tcsrchr(argv0, _T('/'));
    if (last_pathsep_pos == NULL)
        last_pathsep_pos = _tcsrchr(argv0, _T('\\'));

    last_dot_pos = _tcsrchr(argv0, _T('.'));

    if (last_pathsep_pos != NULL)
    {
        pos = last_pathsep_pos + 1 - argv0;

        if (last_dot_pos != NULL && last_dot_pos > last_pathsep_pos)
            count = last_dot_pos - last_pathsep_pos - 1;
        else
            count = str_npos;
    }
    else
    {
        pos = 0;

        if (last_dot_pos != NULL)
            count = last_dot_pos - argv0;
        else
            count = str_npos;
    }

    return substr(argv0, pos, count);
}


// References:
// libuv:uv_get_process_title
