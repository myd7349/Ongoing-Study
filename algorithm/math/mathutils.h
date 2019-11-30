#ifndef MATHUTILS_H_
#define MATHUTILS_H_

#include <stddef.h>


double sumd(const double *x, unsigned n);

double meand(const double *x, unsigned n);

double vard(const double *x, unsigned n);

double stdd(const double *x, unsigned n);

double covd(const double *x, const double *y, unsigned n);

void convd(const double *u, size_t ulen, const double *v, size_t vlen, double *out);

void squared(const double *x, unsigned n, double *x2);

#define squared_in_place(x, n) squared((x), (n), (x))

#endif // MATHUTILS_H_
