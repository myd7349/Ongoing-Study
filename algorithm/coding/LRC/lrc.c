#include "lrc.h"

#include <assert.h>


uint8_t lrc8(const void *buffer, size_t length)
{
    uint8_t checksum = 0;
    size_t i;
    const uint8_t *bytes = (const uint8_t *)buffer;

    assert(buffer != NULL);

    for (i = 0; i < length; ++i)
        checksum = (checksum + bytes[i]) & 0xFF;

    return ((checksum ^ 0xFF) + 1) & 0xFF;
}


// References:
// Longitudinal redundancy check
