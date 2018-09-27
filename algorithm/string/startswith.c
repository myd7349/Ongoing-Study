#include "startswith.h"

#include <assert.h>
#include <string.h>

#ifdef __linux__
# include <strings.h>
#endif


bool startswith(const _TCHAR *s, const _TCHAR *s2)
{
    return startswithex(s, s2, _tcslen(s2));
}


bool startswithi(const _TCHAR *s, const _TCHAR *s2)
{
    return startswithiex(s, s2, _tcslen(s2));
}


bool startswithex(const _TCHAR *s, const _TCHAR *s2, size_t count)
{
    assert(count <= _tcslen(s2));
    return _tcsncmp(s, s2, count) == 0;
}


bool startswithiex(const _TCHAR *s, const _TCHAR *s2, size_t count)
{
    assert(count <= _tcslen(s2));
    return _tcsnicmp(s, s2, count) == 0;
}

// References:
// TortoiseGit/src/Utils/StringUtils.cpp
// Ongoing-Study/cpp/strutils.hpp
// https://linux.die.net/man/3/strcasecmp
