#include "BooleanArray.h"
#include "Win32Common.h"

#include <sstream>

void CopyBooleanArray(bool source[], bool target[], int nitems)
{
    static_assert(sizeof(bool) == 1, "sizeof(bool) required to be 1");

    for (auto i = 0; i < nitems; ++i)
    {
        target[i] = source[i];

        std::ostringstream oss;
        oss << (void *)(source+i) << (source[i] ? ": true" : ": false");

        MessageBoxA(NULL, oss.str().c_str(), "", MB_OK);
    }
}