#pragma once

#include "endian/endian.h"


enum Endian
{
    LittleEndian,
    BigEndian,
};


inline Endian GetHostEndian()
{
    return PSNIP_ENDIAN_ORDER == PSNIP_ENDIAN_LITTLE ? LittleEndian : BigEndian;
}


inline psnip_uint16_t ConvertEndian16(psnip_uint16_t x, Endian endian)
{
    if (endian == LittleEndian)
        return psnip_endian_le16(x);
    else
        return psnip_endian_be16(x);
}


inline psnip_uint32_t ConvertEndian32(psnip_uint32_t x, Endian endian)
{
    if (endian == LittleEndian)
        return psnip_endian_le32(x);
    else
        return psnip_endian_be32(x);
}


inline const char *GetEndianName(Endian endian)
{
    switch (endian)
    {
    case LittleEndian: return "Little Endian"; break;
    case BigEndian: return "Big Endian"; break;
    default: return "Unknown Endian"; break;
    }
}


// References:
// https://github.com/nemequ/portable-snippets/blob/master/endian/endian.h
// https://github.com/caryll/otfcc/blob/master/lib/support/bin-io.h
// https://github.com/mandreyel/endian/blob/master/endian.hpp
// https://github.com/managarm/mlibc/blob/master/options/glibc/include/endian.h
