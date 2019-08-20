#pragma once

#include <stdint.h>

#include "always_inline.h"


#include <stdint.h>

#include "always_inline.h"


static ALWAYS_INLINE uint16_t ya_byteswap_u16(uint16_t v)
{
    return ((v & 0xFF) << 8) | ((v & 0xFF00) >> 8);
}


static ALWAYS_INLINE uint32_t ya_byteswap_u32(uint32_t v)
{
    v = (v >> 16) | (v << 16);
    return ((v & 0xFF00FF00) >> 8) | ((v & 0x00FF00FF) << 8);
}


static ALWAYS_INLINE uint64_t ya_byteswap_u64(uint64_t v)
{
    // swap adjacent 32-bit blocks
    v = (v >> 32) | (v << 32);
    // swap adjacent 16-bit blocks
    v = ((v & 0xFFFF0000FFFF0000LL) >> 16) | ((v & 0x0000FFFF0000FFFFLL) << 16);
    // swap adjacent 8-bit blocks
    return ((v & 0xFF00FF00FF00FF00LL) >> 8) | ((v & 0x00FF00FF00FF00FFLL) << 8);
}


// References:
// https://stackoverflow.com/questions/19560436/bitwise-endian-swap-for-various-types
