#include "base64.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>


static const uint8_t normal_base64_encoding_table[] = 
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};


static const uint8_t urlsafe_base64_encoding_table[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
};


static inline const unsigned char *base64_encoding_table(B64_FLAGS flags)
{
    if (flags & B64F_URLSAFE)
        return urlsafe_base64_encoding_table;
    else
        return normal_base64_encoding_table;
}


// ALIGN_UP(num, 3):
// 0 -> 0
// 1 -> 3
// 2 -> 3
// 3 -> 3
// 4 -> 6
// 5 -> 6
#define ALIGN_UP(num, a) (((num) + (a) - 1) / (a) * (a))


size_t base64_encoded_length(size_t len, B64_FLAGS flags)
{
    // len * 4 / 3 + 4; // otfcc
    // (len + 2) / 3 * 4; // kbase
    // len / 3 * 4 + (len % 3 != 0 ? 4 : 0); // my version
    size_t encoded_len = ALIGN_UP(len, 3) / 3 * 4;

    if (flags & B64F_NO_PADDING)
    {
        size_t remained_bytes = len % 3;
        if (remained_bytes > 0)
        {
            size_t padded_bytes = 3 - remained_bytes;
            encoded_len -= padded_bytes;
        }
    }

    return encoded_len;
}


void *base64_encode(const void *data, size_t len, void *out_buffer, size_t *out_len, B64_FLAGS flags)
{
    size_t remained_bytes = len % 3;
    const uint8_t *in = data;
    const uint8_t *upfront_end = in + (len - remained_bytes);

    size_t expected_out_len = base64_encoded_length(len, flags);
    uint8_t *out_pos = out_buffer;
    
    const uint8_t *table = base64_encoding_table(flags);

    assert(out_len != NULL);

    if (*out_len < expected_out_len)
    {
        *out_len = 0;
        return NULL;
    }

    while (in < upfront_end)
    {
        *out_pos++ = table[in[0] >> 2];
        *out_pos++ = table[((in[0] & 0x3) << 4) | (in[1] >> 4)];
        *out_pos++ = table[(in[1] & 0xF) << 2 | (in[2] >> 6)];
        *out_pos++ = table[in[2] & 0x3F];
        in += 3;
    }

    if (remained_bytes == 1)
    {
        *out_pos++ = table[in[0] >> 2];
        *out_pos++ = table[((in[0] & 0x3) << 4)];

        if ((flags & B64F_NO_PADDING) == 0)
        {
            *out_pos++ = '=';
            *out_pos++ = '=';
        }
    }
    else if (remained_bytes == 2)
    {
        *out_pos++ = table[in[0] >> 2];
        *out_pos++ = table[((in[0] & 0x3) << 4) | (in[1] >> 4)];
        *out_pos++ = table[(in[1] & 0xF) << 2];

        if ((flags & B64F_NO_PADDING) == 0)
            *out_pos++ = '=';
    }

    *out_len = out_pos - (uint8_t *)out_buffer;

    return out_buffer;
}


static inline size_t get_padded_bytes(const uint8_t *base64, size_t len)
{
    if (len < 2)
        return 0;

    assert(base64 != NULL);

    if (len < 4 || base64[len - 1] != '=')
        return 0;

    if (base64[len - 2] != '=')
        return 1;
    else
        return 2;
}


size_t base64_decoded_length_unchecked(const void *base64, size_t len, B64_FLAGS flags)
{
    size_t padded_bytes;
    size_t remained_bytes;

    if (len == 0)
        return 0;

    assert(base64 != NULL);

    padded_bytes = get_padded_bytes(base64, len);

    if (flags & B64F_NO_PADDING)
    {
        assert(padded_bytes == 0);
        if (padded_bytes != 0) // Invalid base64
            return 0;

        remained_bytes = len % 4;
        if (remained_bytes == 0)
        {
            return len / 4 * 3;
        }
        else
        {
            assert(remained_bytes == 2 || remained_bytes == 3);
            if (remained_bytes == 1) // Invalid base64
                return 0;
            else
                return len / 4 * 3 + (remained_bytes - 1);
        }
    }
    else
    {
        assert(len % 4 == 0);
        if (len % 4 != 0) // Invalid base64
            return 0;

        return len / 4 * 3 - padded_bytes;
    }
}


static inline bool base64_table_contains(const uint8_t *table, uint8_t ch)
{
    uint8_t last = table[64 - 1];
    uint8_t last_but_one = table[64 - 2];

    return isalnum(ch) || ch == last || ch == last_but_one;
}


size_t base64_decoded_length_slow(const void *base64, size_t len, B64_FLAGS flags)
{
    const uint8_t *pos = base64;
    const uint8_t *base64_end = pos + (len - get_padded_bytes(base64, len));

    const uint8_t *table = base64_encoding_table(flags);

    while (pos < base64_end)
    {
        if (!base64_table_contains(table, *pos))
            return 0;

        ++pos;
    }

    return base64_decoded_length_unchecked(base64, len, flags);
}


bool base64_is_valid(const void *base64, size_t len, B64_FLAGS flags, size_t *decoded_len)
{
    size_t expected_len = base64_decoded_length_slow(base64, len, flags);
    if (len > 0 && expected_len == 0)
        return false;

    if (decoded_len != NULL)
        *decoded_len = expected_len;

    return true;
}


static const uint8_t *base64_decoding_table(B64_FLAGS flags)
{
    static bool normal_decoding_table_initialized = false;
    static uint8_t normal_decoding_table[256];

    static bool urlsafe_decoding_table_initialized = false;
    static uint8_t urlsafe_decoding_table[256];

    if (flags & B64F_URLSAFE)
    {
        if (!urlsafe_decoding_table_initialized)
        {
            const uint8_t *encoding_table = base64_encoding_table(flags);
            size_t i;

            memset(urlsafe_decoding_table, 0xFF, 256);
            for (i = 0; i < 64; ++i)
                urlsafe_decoding_table[encoding_table[i]] = (uint8_t)i;

            urlsafe_decoding_table_initialized = true;
        }

        return urlsafe_decoding_table;
    }
    else
    {
        if (!normal_decoding_table_initialized)
        {
            const uint8_t *encoding_table = base64_encoding_table(flags);
            size_t i;

            memset(normal_decoding_table, 0xFF, 256);
            for (i = 0; i < 64; ++i)
                normal_decoding_table[encoding_table[i]] = (uint8_t)i;

            normal_decoding_table_initialized = true;
        }

        return normal_decoding_table;
    }
}



void *base64_decode(const void *base64, size_t len, void *data, size_t *out_len, B64_FLAGS flags)
{
    size_t padded_bytes = get_padded_bytes(base64, len);
    size_t remained_bytes;

    const uint8_t *in = base64;
    const uint8_t *in_upfront_end = NULL;
    uint8_t *out = data;

    const uint8_t *decoding_table = base64_decoding_table(flags);

    uint8_t block[4];

    size_t decoded_len_unchecked = base64_decoded_length_unchecked(base64, len, flags);
    if (decoded_len_unchecked == 0)
    {
        if (out_len != NULL)
            *out_len = 0;
        return NULL;
    }

    assert(data != NULL && out_len != NULL);

    if (*out_len < decoded_len_unchecked)
    {
        *out_len = 0;
        return NULL;
    }

    remained_bytes = padded_bytes > 0 ? (4 - padded_bytes) : len % 4;
    in_upfront_end = in + (len - remained_bytes - padded_bytes);

    while (in < in_upfront_end)
    {
        block[0] = decoding_table[in[0]];
        block[1] = decoding_table[in[1]];
        block[2] = decoding_table[in[2]];
        block[3] = decoding_table[in[3]];

        if ((block[0] | block[1] | block[2] | block[3]) >= 64)
        {
            *out_len = 0;
            return NULL;
        }

        *out++ = block[0] << 2 | block[1] >> 4;
        *out++ = (block[1] & 0xF) << 4 | block[2] >> 2;
        *out++ = (block[2] & 0x3) << 6 | block[3];

        in += 4;
    }

    if (remained_bytes == 2)
    {
        block[0] = decoding_table[in[0]];
        block[1] = decoding_table[in[1]];

        if ((block[0] | block[1]) >= 64)
        {
            *out_len = 0;
            return NULL;
        }

        *out++ = block[0] << 2 | block[1] >> 4;
    }
    else if (remained_bytes == 3)
    {
        block[0] = decoding_table[in[0]];
        block[1] = decoding_table[in[1]];
        block[2] = decoding_table[in[2]];

        if ((block[0] | block[1] | block[2]) >= 64)
        {
            *out_len = 0;
            return NULL;
        }

        *out++ = block[0] << 2 | block[1] >> 4;
        *out++ = (block[1] & 0xF) << 4 | block[2] >> 2;
    }

    *out_len = out - (uint8_t *)data;

    return data;
}


char *easy_base64_encode(const void *data, size_t len, char *out, size_t out_len)
{
    size_t encoded_len = out_len;
    uint8_t *result = base64_encode(data, len, out, &encoded_len, B64F_NORMAL);
    if (result == NULL || encoded_len >= out_len)
        return NULL;

    out[encoded_len] = '\0';
    return out;
}


void *easy_base64_decode(const char *base64, void *data, size_t *out_len)
{
    return base64_decode(base64, strlen(base64), data, out_len, B64F_NORMAL);
}


// References:
// https://www.liaoxuefeng.com/wiki/897692888725344/949441536192576
// https://github.com/caryll/otfcc/tree/master/lib/support/base64
// https://github.com/caryll/otfcc/blob/ad01e3608293a548bedf87704f35e4c0529804d3/lib/support/base64/base64.c#L7-L43
// https://github.com/kingsamchen/KBase/blob/master/kbase/base64.cpp
// https://github.com/kingsamchen/KBase/blob/5596e40a215babec40b202a9970308af9522b20f/kbase/base64.cpp#L103-L157
// https://stackoverflow.com/questions/6098288/c-how-convert-wide-string-to-base64
// libsodium: sodium_bin2base64
// https://github.com/ReneNyffenegger/cpp-base64
// https://github.com/cr-marcstevens/snippets/blob/master/cxxheaderonly/base64.hpp
// https://github.com/WojciechMula/base64-avx512
// https://github.com/WojciechMula/toys/tree/master/base64
// https://github.com/tplgy/cppcodec/blob/master/cppcodec/base64_url.hpp
// https://github.com/powturbo/Turbo-Base64
// A comment about base64 from Frank:
// > Encode to hex. Seriously. It’s url-safe and sql-safe.
//   It compresses better than base64, it faster and trivial
//   to safely encode/decode, no padding mess, no incompatibilities
//   between decoders (due to how they handle non-zero padding bits).
// https://twitter.com/jedisct1/status/1413525125459333126
// https://github.com/libb64/libb64
// https://github.com/uutils/coreutils/blob/master/src/uu/base64/src/base64.rs
// https://github.com/wertarbyte/coreutils/blob/master/src/base64.c
// https://github.com/ARMmbed/mbedtls/blob/development/include/mbedtls/base64.h
// https://github.com/tdlib/td/blob/master/tdutils/td/utils/base64.cpp
// [Base64 vs HEX for sending binary content over the internet in XML doc](https://stackoverflow.com/questions/3183841/base64-vs-hex-for-sending-binary-content-over-the-internet-in-xml-doc)
// https://github.com/jedisct1/d8code
// https://github.com/BuLogics/libb64
// https://chromium.googlesource.com/chromium/src/+/refs/heads/main/base/base64.cc
// https://chromium.googlesource.com/chromium/src/+/refs/heads/main/base/base64url.cc
// https://github.com/ncbi/ncbi-cxx-toolkit-public/blob/master/include/connect/ncbi_base64.h
// https://github.com/qiniu/c-sdk/tree/master/b64
// https://github.com/nanomsg/nng/blob/master/src/supplemental/base64/base64.c
// https://github.com/aklomp/base64
// https://github.com/zhicheng/base64
// https://github.com/joedf/base64.c
// https://github.com/MaskRay/ell/blob/master/ell/base64.h
