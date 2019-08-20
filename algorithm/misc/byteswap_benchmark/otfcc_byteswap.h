#pragma once

#include <stdint.h>

#include "always_inline.h"


static ALWAYS_INLINE uint16_t otfcc_byteswap_u16(uint16_t x)
{
    union
	{
        uint8_t i1[2];
        uint16_t i2;
    } src, dst;

    src.i2 = x;

    dst.i1[0] = src.i1[1];
    dst.i1[1] = src.i1[0];

    return dst.i2;
}


static ALWAYS_INLINE uint32_t otfcc_byteswap_u32(uint32_t i) {
    union
	{
        uint8_t i1[4];
        uint32_t i4;
    } src, dst;

    src.i4 = i;

    dst.i1[0] = src.i1[3];
    dst.i1[1] = src.i1[2];
    dst.i1[2] = src.i1[1];
    dst.i1[3] = src.i1[0];

    return dst.i4;
}


static ALWAYS_INLINE uint64_t otfcc_byteswap_u64(uint64_t i)
{
    union
	{
        uint8_t i1[8];
        uint64_t i8;
    } src, dst;

    src.i8 = i;

    dst.i1[0] = src.i1[7];
    dst.i1[1] = src.i1[6];
    dst.i1[2] = src.i1[5];
    dst.i1[3] = src.i1[4];
    dst.i1[4] = src.i1[3];
    dst.i1[5] = src.i1[2];
    dst.i1[6] = src.i1[1];
    dst.i1[7] = src.i1[0];

    return dst.i8;
}


// References:
// https://github.com/caryll/otfcc/blob/master/lib/support/bin-io.h
