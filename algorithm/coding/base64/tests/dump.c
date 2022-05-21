#include "dump.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>


static void dump_data_impl(const char *data, size_t size)
{
    assert(data != NULL || size == 0);

    for (size_t i = 0; i < size; ++i)
    {
        if (isprint((unsigned char)data[i]))
            printf("%c", data[i]);
        else
            printf("\\x%02x", (unsigned char)data[i]);
    }

    printf("\n");
}


void dump_data(const void *data, size_t size)
{
    dump_data_impl(data, size);
}


// References:
// [hexdump(): A memory layout utility to help debugging / understanding / optimising of C++ memory model](https://codereview.stackexchange.com/questions/236039/hexdump-a-memory-layout-utility-to-help-debugging-understanding-optimisin)
