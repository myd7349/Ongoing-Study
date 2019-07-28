#include "bin2hex.h"

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
// libsodium:sodium_bin2hex
// Python: binascii.b2a_hex
