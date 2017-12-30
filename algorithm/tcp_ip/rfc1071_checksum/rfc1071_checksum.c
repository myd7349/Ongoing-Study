#include "rfc1071_checksum.h"

#include <assert.h>


uint16_t rfc1071_checksum(const void *data, size_t count)
{
    uint32_t sum = 0;

    assert(data != NULL);

    while (count > 1)
    {
        sum += *(uint16_t *)data++;
        count -= 2;
    }

    if (count > 0)
        sum += *(uint8_t *)data;

    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return (uint16_t)(~sum);
}


// References:
// https://tools.ietf.org/html/rfc1071
// https://tools.ietf.org/html/rfc1141
// Computer Networks: A Top-Down Approach, 5th Edition, Chapter 3.3
