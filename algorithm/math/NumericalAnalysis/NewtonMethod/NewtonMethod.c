#include "NewtonMethod.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>


int NewtonMethod(math_fn_t f, math_fn_t fprime,
    double x0, double tolerance, double epsilon,
    int max_iterations, double *root)
{
    int i;
    double x1;
    double y;
    double yprime;

    assert(f != NULL && fprime != NULL);
    assert(tolerance > 0.0 && epsilon > 0.0);
    assert(max_iterations > 0);
    assert(root != NULL);

    for (i = 0; i < max_iterations; ++i)
    {
        y = f(x0);
        yprime = fprime(x0);

        if (fabs(yprime) < epsilon)
            break;

        x1 = x0 - y / yprime;
        if (fabs(x1 - x0) <= tolerance * fabs(x1))
        {
            *root = x1;
            return i + 1;
        }

        x0 = x1;
    }

    return -1;
}


// References:
// https://en.wikipedia.org/wiki/Newton%27s_method
// Mastering Algorithms with C, Kyle London, 1999
