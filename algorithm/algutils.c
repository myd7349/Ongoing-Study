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


#define GT(x, y) ((x) > (y))
#define LT(x, y) ((x) < (y))


MOST_T(maxi, int, GT)
MOST_T(maxu, unsigned, GT)

MOST_T(mini, int, LT)
MOST_T(minu, unsigned, LT)


#define PRINTV_T(fn, T, fmt) \
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
        printf(",%d", data[i]); \
    printf("]\n"); \
}


PRINTV_T(printvi, int, d)
PRINTV_T(printvu, unsigned, u)
