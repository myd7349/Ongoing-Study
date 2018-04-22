#include <assert.h>
#include <stdio.h>

#include "../../../algutils.h"
#include "approximate_integration.h"


double rational_func_x_1(double x, void *params)
{
    (void)params;
    assert(x != 0.0);
    return 1 / x;
}


double data_traffic_func(double x, void *params)
{
    // [1] P538
    double traffic[] =
    {
        3.2,
        2.7,
        1.9,
        1.7,
        1.3,
        1.0,
        1.1,
        1.3,
        2.8,
        5.7,
        7.1,
        7.7,
        7.9,
    };

    int hour = (int)(x / 3600.0);

    (void)params;
    assert(hour >= 0 && hour < ARRAYSIZE(traffic));

    return traffic[hour];
}


int main()
{
    double result;
    math_fn_t func = { NULL, NULL };
    int ns[] = { 5, 10, 20 };
    int i;

    // [1] P532 EXAMPLE 1
    func.func = rational_func_x_1;

    printf("n\tLn\t\tRn\t\tTn\t\tMn\t\tSn\n");
    printf("--------------------------------------------------------------------------------\n");

    for (i = 0; i < ARRAYSIZE(ns); ++i)
    {
        int n = ns[i];

        printf("%d\t", n);

        riemann_sum(&func, 1.0, 2.0, n, LEFT_HAND, &result);
        printf("%.6f\t", result);

        riemann_sum(&func, 1.0, 2.0, n, RIGHT_HAND, &result);
        printf("%.6f\t", result);

        trapezoidal_rule_sum(&func, 1.0, 2.0, n, &result);
        printf("%.6f\t", result);

        mid_point_rule_sum(&func, 1.0, 2.0, n, &result);
        printf("%.6f\t", result);

        simpson_rule_sum(&func, 1.0, 2.0, n, &result);
        printf("%.6f\n", result);
    }

    printf("--------------------------------------------------------------------------------\n");

    // [1] P537 EXAMPLE 5
    func.func = data_traffic_func;
    simpson_rule_sum(&func, 0, 43200, 12, &result);
    printf("%.6f\n", result);

    return 0;
}


// References:
// [1] Calculus, 7ed, James.Stewart, P530, Chapter 7.7
