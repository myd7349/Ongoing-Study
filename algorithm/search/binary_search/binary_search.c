#include "binary_search.h"

#include <assert.h>
#include <stdio.h>


void *binary_search(const void *key, const void *ptr, size_t count, size_t size, cmp_fn_t cmp)
{
    size_t left = 0;
    size_t right = count - 1;

    assert(key != NULL && ptr != NULL && count > 0 && size > 0);
    assert(cmp != NULL);

    while (left <= right)
    {
        size_t middle = (left + right) / 2;
        void *elem = (char *)key + middle * size;
        int res = cmp(elem, ptr);

        if (res < 0)
            left = middle + 1;
        else if (res > 0)
            right = middle - 1;
        else
            return elem;
    }

    return NULL;
}


// References:
// Ongoing-Study\c#\Console\INI\INITest\INITest\Program.cs
