// 2017-11-23T16:13+08:00
#ifndef NEWTON_METHOD_H_
#define NEWTON_METHOD_H_

typedef double math_fn_t(double);

// f: y = f(x)
// fprime: y = f'(x), the first derivative of f(x)
// x0: the root we guess
// tolerance: digit accuracy is desired
// epsilon: don't want to divide by a number smaller than this
// max_iterations: max iteration count
// root: the returned root will be stored in root
int NewtonMethod(math_fn_t f, math_fn_t fprime,
    double x0, double tolerance, double epsilon,
    int max_iterations, double *root);

#endif // NEWTON_METHOD_H_
