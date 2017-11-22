// 2017-11-21T19:08+08:00
#ifndef LINEAR_LEAST_SQUARES_H_
#define LINEAR_LEAST_SQUARES_H_

// Simple linear regression by using the linear least squares approach.
// y = a*x + b
void LeastSquaresLinearFit(const double *x, const double *y, int n, double *slope, double *intercept);

#endif // LINEAR_LEAST_SQUARES_H_
