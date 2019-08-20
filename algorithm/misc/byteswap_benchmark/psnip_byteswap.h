#pragma once

#include <stdint.h>

#include "always_inline.h"


static ALWAYS_INLINE uint16_t psnip_builtin_bswap16(uint16_t v)
{
    return
        ((v & (((uint16_t)0xff) << 8)) >> 8) |
        ((v & (((uint16_t)0xff))) << 8);
}


static ALWAYS_INLINE uint32_t psnip_builtin_bswap32(uint32_t v)
{
    return
        ((v & (((uint32_t)0xff) << 24)) >> 24) |
        ((v & (((uint32_t)0xff) << 16)) >> 8) |
        ((v & (((uint32_t)0xff) << 8)) << 8) |
        ((v & (((uint32_t)0xff))) << 24);
}


static ALWAYS_INLINE uint64_t psnip_builtin_bswap64(uint64_t v)
{
    return
        ((v & (((uint64_t)0xff) << 56)) >> 56) |
        ((v & (((uint64_t)0xff) << 48)) >> 40) |
        ((v & (((uint64_t)0xff) << 40)) >> 24) |
        ((v & (((uint64_t)0xff) << 32)) >> 8) |
        ((v & (((uint64_t)0xff) << 24)) << 8) |
        ((v & (((uint64_t)0xff) << 16)) << 24) |
        ((v & (((uint64_t)0xff) << 8)) << 40) |
        ((v & (((uint64_t)0xff))) << 56);
}


// References:
// https://github.com/nemequ/portable-snippets/blob/77654dbc376e0465aaae096553eeb2e95a9f2735/builtin/builtin.h#L974-L1017
