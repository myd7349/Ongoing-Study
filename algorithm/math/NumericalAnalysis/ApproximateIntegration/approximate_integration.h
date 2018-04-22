// 2018-04-22T14:12+08:00
#ifndef APPROXIMATE_INTEGRATION_H_
#define APPROXIMATE_INTEGRATION_H_

#include "../../mathfunc.h"


typedef enum
{
    LEFT_HAND,
    MID_POINT,
    RIGHT_HAND
} riemann_sum_strategy_t;


int riemann_sum(math_fn_t *func, double a, double b, int n, riemann_sum_strategy_t strategy, double *result);

int mid_point_rule_sum(math_fn_t *func, double a, double b, int n, double *result);

int trapezoidal_rule_sum(math_fn_t *func, double a, double b, int n, double *result);

int simpson_rule_sum(math_fn_t *func, double a, double b, int n, double *result);

#endif // APPROXIMATE_INTEGRATION_H_
