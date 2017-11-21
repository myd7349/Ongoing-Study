#include "NewtonPolynomialInterpolation.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


void DividedDifferences(const double *x, const double *fx, int n, double *slopes)
{
    int i, j;

    assert(x != NULL && fx != NULL && n > 1 && x[0] < x[n-1]);
    assert(slopes != NULL);

    memcpy(slopes, fx, sizeof(double) * n);

    // Suppose we got:
    // x: x0, x1, x2, x3
    // fx: f(x0), f(x1), f(x2), f(x3)
    // After the first inner loop we got:
    // slopes: { f(x0), f(x1,x0), f(x2,x1), f(x3,x2) }
    // After the second inner loop we got:
    // slopes: { f(x0), f(x1,x0), f(x2,x1,x0), f(x3,x2,x1) }
    // After the third inner loop:
    // slopes: { f(x0), f(x1,x0), f(x2,x1,x0), f(x3,x2,x1,x0) }
    for (i = 0; i < n - 1; ++i)
    {
        for (j = n - 1; j > i; --j)
        {
            assert(x[j] - x[j-1] > 0.0);
            slopes[j] = (slopes[j] - slopes[j-1]) / (x[j] - x[j-i-1]);
        }
    }
}


void NewtonPolynomialInterpolation(const double *x, const double *slopes, int n,
    const double *z, double *pz, int m)
{
    int i, j;

    assert(x != NULL && slopes != NULL && n > 1 && x[0] < x[n-1]);
    assert(z != NULL && pz != NULL && m > 0);

    for (i = 0; i < m; ++i)
    {
        double temp = 1.0;
        pz[i] = slopes[0];

        for (j = 1; j < n; ++j)
        {
            temp *= z[i] - x[j-1];
            pz[i] += slopes[j] * temp;
        }
    }
}


int SimpleNewtonPolynomialInterpolation(const double *x, const double *fx, int n,
    const double *z, double *pz, int m)
{
    double *slopes = NULL;

    assert(n > 0);
    slopes = malloc(n * sizeof(double));
    if (slopes == NULL)
        return 1;

    DividedDifferences(x, fx, n, slopes);
    NewtonPolynomialInterpolation(x, slopes, n, z, pz, m);

    free(slopes);

    return 0;
}


// References:
// https://en.wikipedia.org/wiki/Divided_differences
// https://en.wikipedia.org/wiki/Newton_polynomial
// Mastering Algorithms with C, Kyle London, 1999
