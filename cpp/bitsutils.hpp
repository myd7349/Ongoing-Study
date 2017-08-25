// 2016-11-24T14:05+08:00
#ifndef BITSUTILS_HPP_
#define BITSUTILS_HPP_

#include <cassert>
#include <cstdio>

// TODO: Concepts

template <typename T>
inline T &SetBit(T &value, T pos)
{
	assert(pos >= 0 && pos < sizeof(T) * 8);
	value |= 0x1 << pos;
	return value;
}

template <typename T>
inline bool IsBitSet(T value, T pos)
{
	assert(pos >= 0 && pos < sizeof(T) * 8);
	return value & (0x1 << pos); 
}

template <typename T>
inline T GetBit(T value, T pos)
{
	return IsBitSet(value, pos) ? 1 : 0;
}

template <typename T>
inline T &ClearBit(T &value, T pos)
{
	assert(pos >= 0 && pos < sizeof(T) * 8);
	value &= ~(0x1 << pos);
	return value;
}

template <typename T>
inline T &TriggleBit(T &value, T pos, bool set)
{
    return set ? SetBit(value, pos) : ClearBit(value, pos);
}

template <typename T>
inline T &SwapBit(T &value, T pos1, T pos2)
{
	if (pos1 == pos2)
		return value;

	T b1 = GetBit(value, pos1);
	T b2 = GetBit(value, pos2);
	TriggleBit(value, pos1, b2);
	TriggleBit(value, pos2, b1);

	return value;
}

template <typename T>
inline T &SetBits(T &value, T bits)
{
    value |= bits;
    return value;
}

template <typename T>
inline T &ClearBits(T &value, T bits)
{
    value &= (~bits);
    return value;
}

template <typename T>
inline T &TriggleBits(T &value, T bits, bool set)
{
    return set ? SetBits(value, bits) : ClearBits(value, bits);
}

template <typename T>
inline bool IsBitsSet(T value, T bits)
{
    return (value & bits) != 0;
}

template <typename T>
void PrintBits(T bits)
{
	for (int i = sizeof(T) * 8 - 1; i >= 0; --i)
		std::putchar(GetBit(bits, static_cast<T>(i)) == 1 ? '1' : '0');
}

#endif // BITSUTILS_HPP_
