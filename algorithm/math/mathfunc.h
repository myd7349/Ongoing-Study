// 2018-04-22T14:22+08:00
#ifndef MATH_FUNCTION_H_
#define MATH_FUNCTION_H_

// A `gsl_function` likely stuff.
typedef struct
{
    double (*func)(double x, void *params);
    void *params;
} math_fn_t;

#endif // MATH_FUNCTION_H_
