// 2017-08-25T14:28+08:00
#ifndef BITUTILS_H_
#define BITUTILS_H_

#include <assert.h>
#include <limits.h>
#include <stdio.h>


#define SET_BIT(v, p) \
    do \
    { \
        assert((p) >= 0 && (p) < sizeof(v) * CHAR_BIT); \
        ((v) |= 0x1 << (p)); \
    } while (0)


#define IS_BIT_SET(v, p) \
    ( \
        assert((p) >= 0 && (p) < sizeof(v) * CHAR_BIT), \
        ((0x1 << (p)) & (v)) \
    )


// y = (x >> n) & 1;
#define GET_BIT(v, p) (IS_BIT_SET((v), (p)) ? 1 : 0)


#define CLEAR_BIT(v, p) \
    do \
    { \
        assert((p) >= 0 && (p) < sizeof(v) * CHAR_BIT); \
        ((v) &= ~(0x1 << (p))); \
    } while (0)


// x ^= (1 << n);
#define TRIGGLE_BIT(v, p, b) \
    do \
    { \
        if (b) \
            SET_BIT((v), (p)); \
        else \
            CLEAR_BIT((v), (p)); \
    } while (0)


#define SWAP_BIT(v, p1, p2) \
    do \
    { \
        if ((p1) != (p2)) \
        { \
            unsigned char b1 = GET_BIT((v), (p1)); \
            unsigned char b2 = GET_BIT((v), (p2)); \
            TRIGGLE_BIT((v), (p1), (b2)); \
            TRIGGLE_BIT((v), (p2), (b1)); \
        } \
    } while (0)


#define PRINT_BITS(v) \
    do \
    { \
        int i; \
        for (i = sizeof(v) * CHAR_BIT - 1; i >= 0; --i) \
            putchar(IS_BIT_SET((v), i) ? '1' : '0'); \
    } while (0)


#define PRINT_BITS_EX(v, sp, nl) \
    do \
    { \
        int i; \
        int counter = 0; \
        for (i = sizeof(v) * CHAR_BIT - 1; i >= 0; --i) \
        { \
            putchar(IS_BIT_SET((v), i) ? '1' : '0'); \
            ++counter; \
            if (counter == sp && i != 0) \
            { \
                putchar(' '); \
                counter = 0; \
            } \
        } \
        if (nl) \
            putchar('\n'); \
    } while (0)


#endif // BITUTILS_H_


// References:
// https://swharden.com/blog/2009-06-24-reading-writing-and-flipping-bits-in-c/
// leave the lowest N bits of x alone and set higher bits to 0.
// x &= (1 << (n + 1)) - 1;
// toggle every bit of x
// x = ~x;
// https://github.com/OpenGenus/cosmos/tree/master/code/bit_manipulation
// [Sign extend a nine-bit number in C](https://stackoverflow.com/questions/5814072/sign-extend-a-nine-bit-number-in-c)
// https://graphics.stanford.edu/~seander/bithacks.html#FixedSignExtend
// http://www.c-jump.com/CIS77/CPU/Numbers/U77_0160_sign_extension.htm
// [Bit Padding (C)](https://stackoverflow.com/questions/42910368/bit-padding-c)
// [Rounding up to next power of 2](https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2)
// [Bit Twiddling Hacks](https://graphics.stanford.edu/%7Eseander/bithacks.html#RoundUpPowerOf2)
// [Round to the nearest power of two](https://stackoverflow.com/questions/4398711/round-to-the-nearest-power-of-two)
// [How does this bitwise operation check for a power of 2?](https://stackoverflow.com/questions/1053582/how-does-this-bitwise-operation-check-for-a-power-of-2)
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Numerics/BitOperations.cs
