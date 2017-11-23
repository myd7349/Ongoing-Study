#include <math.h>
#include <stdio.h>

#include "NewtonMethod.h"


double f_x2_612(double x) { return x * x - 612.0; }
double f_x2_612_prime(double x) { return 2 * x; }

double f2(double x) { return cos(x) - pow(x, 3.0); }
double f2_prime(double x) { return -sin(x) - 3 * x * x; }

double f3(double x) { return pow(x, 3.0) - x * x - 3.0 * x + 1.8; }
double f3_prime(double x) { return 3.0 * x * x - 2.0 * x - 3.0; }

int main()
{
    double root;

    int iterations = NewtonMethod(f_x2_612, f_x2_612_prime, 10.0, 1e-7, 1e-7, 20, &root);
    if (iterations > 0)
        printf("Got the root of x^2-612 = 0 after %d iterations: %f\n", iterations, root);

    iterations = NewtonMethod(f2, f2_prime, 10.0, 1e-7, 1e-7, 20, &root);
    if (iterations > 0)
        printf("Got the root of cos(x) - x^3 = 0 after %d iterations: %f\n", iterations, root);

    iterations = NewtonMethod(f2, f2_prime, .5, 1e-7, 1e-7, 20, &root);
    if (iterations > 0)
        printf("Got the root of cos(x) - x^3 = 0 after %d iterations: %f\n", iterations, root);

    iterations = NewtonMethod(f3, f3_prime, -2.0, 1e-7, 1e-7, 20, &root);
    if (iterations > 0)
        printf("Got the root of x^3 - x^2 - 3x + 1.8 = 0 after %d iterations: %f\n", iterations, root);

    iterations = NewtonMethod(f3, f3_prime, .5, 1e-7, 1e-7, 20, &root);
    if (iterations > 0)
        printf("Got the root of x^3 - x^2 - 3x + 1.8 = 0 after %d iterations: %f\n", iterations, root);

    iterations = NewtonMethod(f3, f3_prime, 2.0, 1e-7, 1e-7, 20, &root);
    if (iterations > 0)
        printf("Got the root of x^3 - x^2 - 3x + 1.8 = 0 after %d iterations: %f\n", iterations, root);

    iterations = NewtonMethod(f3, f3_prime, 3.0, 1e-7, 1e-7, 20, &root);
    if (iterations > 0)
        printf("Got the root of x^3 - x^2 - 3x + 1.8 = 0 after %d iterations: %f\n", iterations, root);

    return 0;
}
