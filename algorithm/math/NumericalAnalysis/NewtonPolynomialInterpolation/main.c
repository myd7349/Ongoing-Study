#include <stdio.h>

#include "../../../algutils.h"
#include "NewtonPolynomialInterpolation.h"


int main()
{
    double x1[] = { 1.0, 2.0, 3.0, 4.0 };
    double fx1[] = { 6.0, 9.0, 2.0, 5.0 };
    double slopes1[ARRAYSIZE(x1)];

    DividedDifferences(x1, ARRAY(fx1), slopes1);
    printvd(ARRAY(slopes1));

    return 0;
}
