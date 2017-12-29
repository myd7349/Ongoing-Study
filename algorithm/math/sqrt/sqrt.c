#include "sqrt.h"

#include <math.h>


// Newton's method to compute square roots.
double fsqrt(double x)
{
    double epilson = 1e-15;
    double sr = x;

    if (x == 0.0)
        return 0.0;

    if (x < 0.0)
        return NAN;

    while (fabs(sr - x / sr) > epilson * sr)
        sr = (x / sr + sr) / 2.0;

    return sr;
}


// References:
// https://mitpress.mit.edu/sicp/chapter1/node9.html
// https://math.mit.edu/~stevenj/18.335/newton-sqrt.pdf
// Algorithms, 4th Edition, by Robert Sedgewick and Kevin Wayne
// https://stackoverflow.com/questions/4745311/c-division-by-0
