#include "LeastSquaresLinearFit.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>

#include "../../mathutils.h"


// slope = ¦²(X-E[X])(Y-E[Y]) / ¦²(X-E[X])^2
//       = (¦²(X*Y) - n*E[X]*E[Y]) / (¦²(X^2) - n*E[X])
//       = (n*¦²(X*Y) - ¦²(X)*¦²(Y)) / (n*¦²(X^2)-(¦²(X))^2)
//       = Cov(X,Y)/Var(X)
void LeastSquaresLinearFit(const double *x, const double *y, int n, double *slope, double *intercept)
{
    double sumx = 0.0;
    double sumy = 0.0;
    double sumxx = 0.0;
    double sumxy = 0.0;
    int i;

    assert(x != NULL && y != NULL && x != y && n > 1);
    assert(slope != NULL && intercept != NULL && slope != intercept);

    // We can calculate `slope` like this:
    // slope = Cov(x,y)/Var(x)
    // It is too slow, though.
    for (i = 0; i < n; ++i)
    {
        sumx += x[i];
        sumy += y[i];
        sumxx += x[i] * x[i];
        sumxy += x[i] * y[i];
    }

    *slope = (sumxy - sumx * sumy / n) / (sumxx - sumx * sumx / n);
    *intercept = (sumy - *slope * sumx) / n;
}


// References:
// https://zh.wikipedia.org/wiki/%E6%9C%80%E5%B0%8F%E4%BA%8C%E4%B9%98%E6%B3%95
// https://en.wikipedia.org/wiki/Least_squares
// https://en.wikipedia.org/wiki/Linear_least_squares
// https://en.wikipedia.org/wiki/Simple_linear_regression
// Mastering Algorithms with C, Kyle London, 1999
// MATLAB doc polyfit
