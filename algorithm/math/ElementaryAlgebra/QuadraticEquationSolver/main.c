#include <stdio.h>

#include "QuadraticEquationSolver.h"


int main()
{
    QuadraticEquationResult result;

    int res = SolveQuadraticEquation(1.0, -2.0, 1.0, &result); // x^2 - 2*x + 1 = 0
    if (res == 0)
        printf("%f, %f\n", result.x1, result.x2);

    res = SolveQuadraticEquation(1.0, -2.0, -8.0, &result); // (x - 1)^2 = 9
    if (res == 0)
        printf("%f, %f\n", result.x1, result.x2);

    res = SolveQuadraticEquation(1.0, 0.0, 1.0, &result); // x^2 + 1 = 0
    printf("%f, %f\n", result.x1, result.x2);

    return 0;
}
