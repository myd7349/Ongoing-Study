#include "mathutils.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>


#define SUM_T(fn, T) \
T fn(const T *x, unsigned n) \
{ \
    double sum = 0.0; \
    unsigned i; \
    \
    assert(x != NULL && n > 0); \
    \
    for (i = 0; i < n; i++) \
        sum += x[i]; \
    \
    return sum; \
}


SUM_T(sumd, double)


#define MEAN_T(fn, sumfn, T) \
T fn(const T *x, unsigned n) \
{ \
    return sumfn(x, n) / n; \
}


MEAN_T(meand, sumd, double)


// https://en.wikipedia.org/wiki/Variance
// Var(X) = E[(X-E[X])^2] = E[X^2] - E[X]^2 = Cov(X,X)
#define VAR_T(fn, meanfn, T) \
T fn(const T *x, unsigned n) \
{ \
    unsigned i; \
    T squared_deviation_sum = 0.0; \
    T mean; \
    \
    assert(x != NULL && n > 0); \
    \
    if (n == 1) \
        return 0.0; \
    \
    mean = meanfn(x, n); \
    \
    for (i = 0; i < n; ++i) \
        squared_deviation_sum += pow(x[i]-mean, 2.0); \
    \
    return squared_deviation_sum / n; \
}


VAR_T(vard, meand, double)


// https://en.wikipedia.org/wiki/Standard_deviation
#define STD_T(fn, varfn, T) \
T fn(const T *x, unsigned n) \
{ \
    return sqrt(varfn(x, n)); \
}


STD_T(stdd, vard, double)


#define COV_T(fn, meanfn, T) \
T fn(const T *x, const T *y, unsigned n) \
{ \
    unsigned i; \
    T deviation_product_sum = 0.0; \
    T u, v; \
    \
    assert(x != NULL && y != NULL && n > 0); \
    \
    u = meanfn(x, n); \
    v = x == y ? u : meanfn(y, n); \
    \
    for (i = 0; i < n; ++i) \
        deviation_product_sum += (x[i] - u) * (y[i] - v); \
    \
    return deviation_product_sum / n; \
}


COV_T(covd, meand, double)


void convd(const double *u, size_t ulen, const double *v, size_t vlen, double *out)
{
    size_t i;
    size_t j;

    size_t olen = ulen + vlen - 1;

    assert(u != NULL && ulen > 0);
    assert(v != NULL && vlen > 0);
    assert(out != NULL);

    for (i = 0; i < olen; ++i)
        out[i] = 0;

    for (i = 0; i < ulen; ++i)
    {
        for (j = 0; j < vlen; ++j)
        {
            out[i + j] += u[i] * v[j];
        }
    }

    // References:
    // https://www.jianshu.com/p/81e0fffe3840
    // MATLAB: conv
    // numpy.convolve
    // https://github.com/numpy/numpy/blob/4e8ab26a17b96b7b0bdd41ba5e2cfac09685d153/numpy/core/src/multiarray/multiarraymodule.c#L1103-L1219
}


#define SQUARE_T(fn, T) \
void fn(const T *x, unsigned n, T *x2) \
{ \
    unsigned i; \
    \
    assert(x != NULL && n > 0 && x2 != NULL); \
    \
    for (i = 0; i < n; ++i) \
        x2[i] = x[i] * x[i]; \
}


SQUARE_T(squared, double)


// References:
// https://github.com/Celtoys/pycgen
