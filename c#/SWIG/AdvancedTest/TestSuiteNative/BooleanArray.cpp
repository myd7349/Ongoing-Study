#include "BooleanArray.h"
#include "Win32Common.h"

#include <sstream>

void CopyBooleanArray(bool source[], bool target[], int nitems)
{
    static_assert(sizeof(bool) == 1, "sizeof(bool) required to be 1");

    unsigned char *sourcePtr = (unsigned char *)(void *)source;
    unsigned char *targetPtr = (unsigned char *)(void *)target;

    for (auto i = 0; i < nitems; ++i)
    {
        targetPtr[i] = sourcePtr[i];

        std::ostringstream oss;
        oss << (void *)(sourcePtr+i) << (sourcePtr[i] ? ": true" : ": false");

        MessageBoxA(NULL, oss.str().c_str(), "", MB_OK);
    }
}