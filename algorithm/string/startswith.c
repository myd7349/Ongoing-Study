#include "startswith.h"

#include <assert.h>
#include <string.h>

#include "cmp.h"


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
    return ncmp(s, s2, count) == 0;
}


bool startswithiex(const _TCHAR *s, const _TCHAR *s2, size_t count)
{
    assert(count <= _tcslen(s2));
    return nicmp(s, s2, count) == 0;
}

// References:
// TortoiseGit/src/Utils/StringUtils.cpp
// Ongoing-Study/cpp/strutils.hpp
// https://github.com/martinmoene/string-view-lite/blob/3d2a4a7ebcc5dbdd55bd00026075c574a13c861b/include/nonstd/string_view.hpp#L767-L770
