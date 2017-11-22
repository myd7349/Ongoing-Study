#include <stdio.h>

#include "../../../algutils.h"
#include "../../mathutils.h"
#include "LeastSquaresLinearFit.h"


int main()
{
    double height[] = { 1.47, 1.50, 1.52, 1.55, 1.57, 1.60, 1.63, 1.65, 1.68, 1.70, 1.73, 1.75, 1.78, 1.80, 1.83 };
    double mass[] = { 52.21, 53.12, 54.48, 55.84, 57.20, 58.57, 59.93, 61.29, 63.11, 64.47, 66.28, 68.10, 69.92, 72.19, 74.46 };
    double slope, intercept;

    double x[] = { -4.0, -3.0, -2.0, -1.5, -0.5, 1.0, 2.0, 3.5, 4.0 };
    double y[] = { -3.0, -1.0, -2.0, -0.5, 1.0, 0.0, 1.5, 1.0, 2.5 };

    LeastSquaresLinearFit(height, ARRAY(mass), &slope, &intercept);
    printf("Slope: %f, Intercept: %f\n", slope, intercept);

    slope = covd(height, ARRAY(mass)) / vard(ARRAY(height));
    printf("Slope via Cov(X,Y)/Var(X): %f\n", slope);\

    LeastSquaresLinearFit(x, ARRAY(y), &slope, &intercept);
    printf("Slope: %f, Intercept: %f\n", slope, intercept);

    return 0;
}
