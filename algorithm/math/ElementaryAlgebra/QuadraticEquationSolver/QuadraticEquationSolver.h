// 2017-11-20T15:16+08:00
#ifndef QUADRATICEQUATIONSOLVER_H_
#define QUADRATICEQUATIONSOLVER_H_

#include <complex.h>

// Solve quadratic equation `a*x^2 + b*x + c = 0`.

typedef struct
{
    double x1;
    double x2;
} QuadraticEquationResult;

int SolveQuadraticEquation(double a, double b, double c, QuadraticEquationResult *result);


#endif // QUADRATICEQUATIONSOLVER_H_
