#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define EPSILON (1e-6)

int double_almost_equal(double x, double y);
double get_epsilon(double x);
int double_almost_equal_v2(double x, double y, double epsilon);

#ifdef __cplusplus
}
#endif
