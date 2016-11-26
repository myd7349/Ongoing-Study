// 2016-11-24T14:05+08:00
#ifndef BITSUTILS_HPP_
#define BITSUTILS_HPP_

// TODO: Concepts

template <typename T>
inline T SetBits(T &value, T bits)
{
    value |= bits;
    return value;
}

template <typename T>
inline T ClearBits(T &value, T bits)
{
    value &= (~bits);
    return value;
}

template <typename T>
inline T TriggleBits(T &value, T bits, bool set)
{
    return set ? SetBits(value, bits) : ClearBits(value, bits);
}

template <typename T>
inline bool IsBitsSet(T value, T bits)
{
    return (value & bits) != 0;
}

#endif // BITSUTILS_HPP_
