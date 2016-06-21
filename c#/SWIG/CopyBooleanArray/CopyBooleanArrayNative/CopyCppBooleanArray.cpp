#include "CopyCppBooleanArray.h"

void CopyBooleanArray(bool source[], bool target[], int nitems)
{
    static_assert(sizeof(bool) == 1, "sizeof(bool) required to be 1");

    for (auto i = 0; i < nitems; ++i)
        target[i] = source[i];
}
