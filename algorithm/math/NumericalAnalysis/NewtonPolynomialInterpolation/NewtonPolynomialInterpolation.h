// 2017-11-21T08:23+08:00
#ifndef NEWTON_POLYNOMIAL_INTERPOLATION_H_
#define NEWTON_POLYNOMIAL_INTERPOLATION_H_

// Calculate the divided differences of a Newton polynomial given by
// `x` and `fx`. The returned result will be stored in `slopes`.
void DividedDifferences(const double *x, const double *fx, int n, double *slopes);

void NewtonPolynomialInterpolation(const double *x, const double *slopes, int n,
    const double *z, double *pz, int m);

int SimpleNewtonPolynomialInterpolation(const double *x, const double *fx, int n,
    const double *z, double *pz, int m);


#endif // NEWTON_POLYNOMIAL_INTERPOLATION_H_
