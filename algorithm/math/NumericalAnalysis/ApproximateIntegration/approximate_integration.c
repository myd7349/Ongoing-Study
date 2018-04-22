#include "approximate_integration.h"

#include <assert.h>
#include <stddef.h>


typedef double (*riemann_sum_strategy_fn_t)(double lhs, double rhs);


double left(double lhs, double rhs)
{
    assert(lhs < rhs);
    return lhs;
}


double right(double lhs, double rhs)
{
    assert(lhs < rhs);
    return rhs;
}


double mid_point(double lhs, double rhs)
{
    assert(lhs < rhs);
    return (lhs + rhs) / 2.0;
}


int riemann_sum_impl(math_fn_t *func, double a, double b, int n, riemann_sum_strategy_fn_t strategy_func, double *result)
{
    double delta_x;
    double lhs, x, rhs;
    double fx;
    int i;

    assert(func != NULL);
    assert(a < b);
    assert(n > 0);
    assert(strategy_func != NULL);
    assert(result != NULL);

    *result = 0.0;
    delta_x = (b - a) / n;
    lhs = a;

    for (i = 0; i < n; ++i)
    {
        rhs = lhs + delta_x;

        x = strategy_func(lhs, rhs); // The One
        fx = func->func(x, func->params);
        *result += fx;

        lhs = rhs;
    }

    *result *= delta_x;

    return 0;
}


int riemann_sum(math_fn_t *func, double a, double b, int n, riemann_sum_strategy_t strategy, double *result)
{
    riemann_sum_strategy_fn_t strategy_func = NULL;

    assert(strategy >= LEFT_HAND && strategy <= RIGHT_HAND);

    switch (strategy)
    {
    case LEFT_HAND: strategy_func = left; break;
    case MID_POINT: strategy_func = mid_point; break;
    case RIGHT_HAND: strategy_func = right; break;
    default: break;
    }

    return riemann_sum_impl(func, a, b, n, strategy_func, result);
}


int mid_point_rule_sum(math_fn_t *func, double a, double b, int n, double *result)
{
    return riemann_sum(func, a, b, n, MID_POINT, result);
}


int trapezoidal_rule_sum(math_fn_t *func, double a, double b, int n, double *result)
{
    int res;
    double delta_x;
    double fx0, fxn;

    assert(func != NULL);
    assert(a < b);
    assert(n > 0);
    assert(result != NULL);

    res = riemann_sum(func, a, b, n, LEFT_HAND, result);
    if (res != 0)
        return res;

    delta_x = (b - a) / n;
    fx0 = func->func(a, func->params);
    fxn = func->func(b, func->params);

    // Now the result is:
    // delta_x * [f(x0) + f(x1) + ... + f(xn-1)]
    // But what we want is:
    // delta_x * [0.5*f(x0) + f(x1) + ... + f(xn-1) + 0.5 * f(xn)]
    *result += delta_x * (fxn - fx0) / 2.0;

    return 0;
}


int simpson_rule_sum(math_fn_t *func, double a, double b, int n, double *result)
{
    double delta_x;
    double x;
    double fx;
    int i;

    assert(func != NULL);
    assert(a < b);
    assert(n > 0);
    assert(result != NULL);

    *result = 0.0;
    delta_x = (b - a) / n;
    x = a;

    *result += func->func(a, func->params);

    for (i = 1; i < n; ++i)
    {
        int coefficient = ((i % 2 == 0) ? 2 : 4);
        x += delta_x;
        fx = func->func(x, func->params);
        *result += coefficient * fx;
    }

    *result += func->func(b, func->params);

    *result *= delta_x / 3.0;

    return 0;
}


// References:
// https://stackoverflow.com/questions/16512817/numerical-integration-in-c
// Ongoing-Study/cpp/gsl/finite_integration_of_x_1.cpp
// Calculus, 7ed, James.Stewart, P530, Chapter 7.7
