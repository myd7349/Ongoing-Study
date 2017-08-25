// 2017-08-25T14:28+08:00
#ifndef BITUTILS_H_
#define BITUTILS_H_

#include <assert.h>
#include <stdio.h>


#define SET_BIT(v, p) \
    do \
    { \
        assert((p) >= 0 && (p) < sizeof(v) * 8); \
        ((v) |= 0x1 << (p)); \
    } while (0)


#define IS_BIT_SET(v, p) \
    ( \
        assert((p) >= 0 && (p) < sizeof(v) * 8), \
        ((0x1 << (p)) & (v)) \
    )


#define GET_BIT(v, p) (IS_BIT_SET((v), (p)) ? 1 : 0)


#define CLEAR_BIT(v, p) \
    do \
    { \
        assert((p) >= 0 && (p) < sizeof(v) * 8); \
        ((v) &= ~(0x1 << (p))); \
    } while (0)


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
        for (i = sizeof(v) * 8 - 1; i >= 0; --i) \
            putchar(IS_BIT_SET((v), i) ? '1' : '0'); \
    } while (0)


#endif // BITUTILS_H_