#include "algutils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


void swap(void *p, void *q, unsigned elem_size, void *temp_elem)
{
    assert(p != NULL && q != NULL);
    assert(elem_size > 0);
    assert(temp_elem != NULL);

    memcpy(temp_elem, p, elem_size);
    memcpy(p, q, elem_size);
    memcpy(q, temp_elem, elem_size);
}


#define MOST_T(fn, T, op) \
T fn(T *data, unsigned size) \
{ \
    unsigned i; \
    T most; \
    \
    assert(data != NULL && size > 0); \
    \
    most = data[0]; \
    for (i = 1; i < size; ++i) \
    { \
        if (op(data[i], most)) \
            most = data[i]; \
    } \
    \
    return most; \
}


MOST_T(maxi, int, GT)
MOST_T(maxu, unsigned, GT)

MOST_T(mini, int, LT)
MOST_T(minu, unsigned, LT)


#define PRINTV_T(fn, T, fmt, nl) \
void fn(T *data, unsigned size) \
{ \
    unsigned i; \
    \
    assert(data != NULL && size >= 0); \
    if (size == 0) \
    { \
        printf("[]\n"); \
        return; \
    } \
    \
    printf("[%" STR(fmt), data[0]); \
    for (i = 1; i < size; ++i) \
        printf(",%" STR(fmt), data[i]); \
    printf("]"); \
    if (nl) printf("\n"); \
}


PRINTV_T(printvi, int, d, 0)
PRINTV_T(printvu, unsigned, u, 0)
PRINTV_T(printvd, double, f, 0)

PRINTV_T(printvinl, int, d, 1)
PRINTV_T(printvunl, unsigned, u, 1)
PRINTV_T(printvdnl, double, f, 1)


#define REVERSE_T(fn, T) \
void fn(T *data, unsigned size) \
{ \
    unsigned i; \
    unsigned stop = size / 2; \
    \
    assert(data != NULL && size >= 0); \
    for (i = 0; i < stop; ++i) \
        SWAP_T(T, data[i], data[size - 1 - i]); \
}


REVERSE_T(reversei, int)
REVERSE_T(reverseu, unsigned)


// [1]
#define ROTATE_T(fn, T) \
void fn(T *data, unsigned size, int shift) \
{ \
    unsigned start = 0; \
    unsigned count = 0; \
    \
    assert(data != NULL && size >= 0); \
    if (size == 0) \
        return; \
    \
    if (shift > 0) \
    { \
        shift = size - shift % size; \
    } \
    else if (shift < 0) \
    { \
        shift = -shift; \
        shift %= size; \
    } \
    \
    if (shift == 0) \
        return; \
    \
    while (count < size) \
    { \
        T tmp = data[start]; \
        unsigned i = start; \
        unsigned j; \
        \
        while (1) \
        { \
            count += 1; \
            j = (i + shift) % size; \
            if (j == start) \
            { \
               data[i] = tmp; \
               break; \
            } \
            \
            data[i] = data[j]; \
            i = (i + shift) % size; \
        } \
        \
        start += 1; \
    } \
}


ROTATE_T(rotatei, int)
ROTATE_T(rotateu, unsigned)


// [1] Programming Pearls, 2nd Edition, Jon Bentley, 2.3
