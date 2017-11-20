#include "QuadraticEquationSolver.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>


int SolveQuadraticEquation(double a, double b, double c, QuadraticEquationResult *result)
{
    double bb_4ac;
    double root_of_bb_4ac;
    double a2;

    assert(result != NULL);

    if (result == NULL)
        return 1;

    result->x1 = result->x2 = NAN;

    if (a == 0.0)
    {
        if (b == 0.0)
            return 1;

        result->x1 = result->x2 = -c / b;
        return 0;
    }

    bb_4ac = b * b - 4 * a * c;
    if (bb_4ac < 0.0)
        return 1;

    root_of_bb_4ac = sqrt(bb_4ac);
    a2 = 2 * a;

    // x1 = (-b - sqrt(b^2 - 4*a*c)) / (2*a)
    // x2 = (-b + sqrt(b^2 - 4*a*c)) / (2*a)
    result->x1 = (-b - root_of_bb_4ac) / a2;
    result->x2 = (-b + root_of_bb_4ac) / a2;

    return 0;
}


// References:
// [Quadratic equation](https://en.wikipedia.org/wiki/Quadratic_equation)
// [Quadratic Equation Solver](https://www.mathsisfun.com/quadratic-equation-solver.html)
//
