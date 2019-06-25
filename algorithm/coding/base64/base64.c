#include "base64.h"

#include <assert.h>
#include <limits.h>


static const uint8_t normal_base64_table[] = 
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};


static const uint8_t urlsafe_base64_table[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
};


// 0 -> 0
// 1 -> 3
// 2 -> 3
// 3 -> 3
// 4 -> 6
// 5 -> 6
#define ALIGN_UP(num, a) (((num) + (a) - 1) / (a) * (a))


size_t base64_encode_length(size_t len)
{
    //return len * 4 / 3 + 4; // otfcc
    //return (len + 2) / 3 * 4; // kbase
    //return len / 3 * 4 + (len % 3 != 0 ? 4 : 0); // my version
    return ALIGN_UP(len, 3) / 3 * 4;
}


// Python:
// import base64
// base64.b64encode
void *base64_encode(const void *data, size_t len, void *out_buffer, size_t *out_len, B64_FLAGS flags)
{
    size_t remained_bytes = len % 3;
    const uint8_t *in = data;
    const uint8_t *upfront_end = in + (len - remained_bytes);

    size_t expected_out_len = base64_encode_length(len);
    uint8_t *out_pos = out_buffer;
    
    const uint8_t *base64_table = normal_base64_table;
    if (flags == B64F_URLSAFE)
        base64_table = urlsafe_base64_table;

    assert(data != NULL);

    if (*out_len < expected_out_len)
    {
        *out_len = 0;
        return NULL;
    }

    while (in < upfront_end)
    {
        *out_pos++ = base64_table[in[0] >> 2];
        *out_pos++ = base64_table[((in[0] & 0x3) << 4) | (in[1] >> 4)];
        *out_pos++ = base64_table[(in[1] & 0xF) << 2 | (in[2] >> 6)];
        *out_pos++ = base64_table[in[2] & 0x3F];
        in += 3;
    }

    if (remained_bytes == 1)
    {
        *out_pos++ = base64_table[in[0] >> 2];
        *out_pos++ = base64_table[((in[0] & 0x3) << 4)];
        *out_pos++ = '=';
        *out_pos++ = '=';
    }
    else if (remained_bytes == 2)
    {
        *out_pos++ = base64_table[in[0] >> 2];
        *out_pos++ = base64_table[((in[0] & 0x3) << 4) | (in[1] >> 4)];
        *out_pos++ = base64_table[(in[1] & 0xF) << 2];
        *out_pos++ = '=';
    }

    *out_len = out_pos - (uint8_t *)out_buffer;

    return out_buffer;
}


char *easy_base64_encode(const uint8_t *data, size_t len, char *out, size_t out_len)
{
    size_t encoded_len = out_len;
    uint8_t *result = base64_encode(data, len, out, &encoded_len, B64F_NORMAL);
    if (result == NULL || encoded_len >= out_len)
        return NULL;

    out[encoded_len] = '\0';
    return out;
}


// References:
// https://www.liaoxuefeng.com/wiki/897692888725344/949441536192576
// https://github.com/caryll/otfcc/tree/master/lib/support/base64
// https://github.com/caryll/otfcc/blob/ad01e3608293a548bedf87704f35e4c0529804d3/lib/support/base64/base64.c#L7-L43
// https://github.com/kingsamchen/KBase/blob/master/kbase/base64.cpp
// https://github.com/kingsamchen/KBase/blob/5596e40a215babec40b202a9970308af9522b20f/kbase/base64.cpp#L103-L157
// https://stackoverflow.com/questions/6098288/c-how-convert-wide-string-to-base64
