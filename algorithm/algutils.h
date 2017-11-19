// 2016-12-30T12:13:31+08:00
#ifndef ALGUTILS_H_
#define ALGUTILS_H_

#include "../c/common.h"

typedef int (*cmp_fn_t)(const void *, const void *);

void swap(void *p, void *q, unsigned elem_size, void *temp_elem);

int maxi(int *data, unsigned size);
unsigned maxu(unsigned *data, unsigned size);

int mini(int *data, unsigned size);
unsigned minu(unsigned *data, unsigned size);

void printvi(int *data, unsigned size);
void printvu(unsigned *data, unsigned size);

#define ARRAY(a) a, ARRAYSIZE(a)

#endif // ALGUTILS_H_
