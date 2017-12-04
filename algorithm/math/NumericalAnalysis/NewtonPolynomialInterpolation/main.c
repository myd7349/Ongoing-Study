#include <stdio.h>

#include "../../../algutils.h"
#include "NewtonPolynomialInterpolation.h"


int main()
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };
    double fx1[] = { 6.0, 9.0, 2.0, 5.0 };
    double slopes1[ARRAYSIZE(x1)];

    double x2[] = { -4.0, -3.5, -2.5, -1.5, 0.0, 1.5, 2.5, 3.5, 4.0 };
    double fx2[] = { -3.0, 1.5, 2.5, 1.5, 0.5, 1.5, 2.5, 1.5, -3.0 };
    double z2[] = { -3.0, -2.0, -1.0 };
    double pz2[ARRAYSIZE(z2)];

    // y = x
    double x3[] = { 0.0, 10.0 };
    double fx3[] = { 0.0, 10.0 };
    double z3[] = { 0.0, 1.0, 2.0, 3.0, 4.0, 100.0 };
    double pz3[ARRAYSIZE(z3)];

    // y = x^2
    double x4[] = { -2.0, -1.0, -0.5, 0.0, 1.0, 2.5, 3.0 };
    double fx4[] = { 4.0, 1.0, 0.25, 0.0, 1.0, 6.25, 9.0 };
    double z4[] = { -1.5, -0.9, -0.8, 0.5, 2.0, 10.0 };
    double pz4[ARRAYSIZE(z4)];

    double x5[] = { -3.0, -2.0, 2.0, 3.0 };
    double fx5[] = { -5.0, -1.1, 1.9, 4.8 };
    double z5[] = { -2.5, 0.0, 2.5 };
    double pz5[ARRAYSIZE(z5)];

    DividedDifferences(x1, ARRAY(fx1), slopes1);
    printvdnl(ARRAY(slopes1));

    SimpleNewtonPolynomialInterpolation(x2, ARRAY(fx2), z2, ARRAY(pz2));
    printvdnl(ARRAY(pz2));

    SimpleNewtonPolynomialInterpolation(x3, ARRAY(fx3), z3, ARRAY(pz3));
    printvdnl(ARRAY(pz3));

    SimpleNewtonPolynomialInterpolation(x4, ARRAY(fx4), z4, ARRAY(pz4));
    printvdnl(ARRAY(pz4));

    SimpleNewtonPolynomialInterpolation(x5, ARRAY(fx5), z5, ARRAY(pz5));
    printvdnl(ARRAY(pz5));

    return 0;
}
