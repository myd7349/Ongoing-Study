// 2016-12-30T12:13:31+08:00
#ifndef ALGUTILS_H_
#define ALGUTILS_H_

#include "../c/common.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define SWAP_T(T, x, y) \
    do { \
        T temp = (x); \
        (x) = (y); \
        (y) = temp; \
    } while (0)

#define GT(x, y) ((x) > (y))
#define LT(x, y) ((x) < (y))

// radix_sortu10(ARRAY(a)); // oops
#define ARRAY(a) a, ARRAYSIZE(a)

typedef int (*cmp_fn_t)(const void *, const void *);

void swap(void *p, void *q, unsigned elem_size, void *temp_elem);

int maxi(int *data, unsigned size);
unsigned maxu(unsigned *data, unsigned size);

int mini(int *data, unsigned size);
unsigned minu(unsigned *data, unsigned size);

void printvi(int *data, unsigned size);
void printvu(unsigned *data, unsigned size);

void reversei(int *data, unsigned size);
void reverseu(unsigned *data, unsigned size);

// n < 0: left rotate
// n > 0: right rotate
void rotatei(int *data, unsigned size, int n);
void rotateu(unsigned *data, unsigned size, int n);

#endif // ALGUTILS_H_
