// 2017-07-15T14:14+08:00
#ifndef LERP_H_
#define LERP_H_

float flerpf(float v0, float v1, float t);
double flerp(double v0, double v1, double t);
long double flerpl(long double v0, long double v1, long double t);

int lerp(int v0, int v1, int t);
long llerp(long v0, long v1, long t);
long long lllerp(long long v0, long long v1, long long t);

#define lerp_fn(T) _Generic((T), \
    long double: flerpl, \
    double: flerp, \
    float: flerpf, \
    int: lerp, \
    long: llerp, \
    long long: lllerp, \
    default: flerp \
    )

#define lerp(v0, v1, t) lerp_fn(v0)(v0, v1, t)

#endif // LERP_H_

// References:
// https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29
// https://gcc.gnu.org/wiki/C11Status
// http://www.robertgamble.net/2012/01/c11-generic-selections.html
