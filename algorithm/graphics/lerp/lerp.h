// 2017-07-15T14:14+08:00
#ifndef LERP_H_
#define LERP_H_

#ifdef __cplusplus
extern "C" {
#endif

float flerpf(float v0, float v1, float t);
double flerp(double v0, double v1, double t);
long double flerpl(long double v0, long double v1, long double t);

int lerp(int v0, int v1, int t);
long llerp(long v0, long v1, long t);
long long lllerp(long long v0, long long v1, long long t);

#ifdef __cplusplus
}
#endif

#define lerp_fn_1(x) _Generic((x), \
    long double: flerpl, \
    double: flerp, \
    float: flerpf, \
    int: lerp, \
    long: llerp, \
    long long: lllerp, \
    default: flerp \
    )

#define lerp_fn_2(v0, v1) _Generic((v0), \
    int: lerp_fn_1(v1), \
    long: _Generic((v1), \
        int: llerp, \
        default: lerp_fn_1(v1) \
        ), \
    long long: _Generic((v1), \
        int: lllerp, \
        long: lllerp, \
        float: flerp, \
        default: lerp_fn_1(v1) \
        ), \
    float: _Generic((v1), \
        int: flerpf, \
        long: flerpf, \
        long long: flerp, \
        default: lerp_fn_1(v1) \
        ), \
    double: _Generic((v1), \
        long double: flerpl, \
        default: flerp \
        ), \
    long double: flerpl \
    )

#define lerp_fn_3(v0, v1, v2) _Generic((v0), \
    int: lerp_fn_2(v1, v2), \
    long: _Generic((v1), \
        int: lerp_fn_2(v0, v2), \
        default: _Generic((v2), \
            int: lerp_fn_2(v0, v1), \
            default: lerp_fn_2(v1, v2) \
            ) \
        ), \
    long long: _Generic((v1), \
        int: lerp_fn_2(v0, v2), \
        long: lerp_fn_2(v0, v2), \
        default: _Generic((v2), \
            int: lerp_fn_2(v0, v1), \
            long: lerp_fn_2(v0, v1), \
            default: lerp_fn_2(v1, v2) \
            ) \
        ), \
    float: _Generic((v1), \
        int: lerp_fn_2(v0, v2), \
        long: lerp_fn_2(v0, v2), \
        default: _Generic((v2), \
            int: lerp_fn_2(v0, v1), \
            long: lerp_fn_2(v0, v1), \
            default: lerp_fn_2(v1, v2) \
            ) \
        ), \
    double: _Generic((v1), \
        long double: flerpl, \
        default: _Generic((v2), \
            long double: flerpl, \
            default: lerp_fn_2(v0, v2) \
            ) \
        ), \
    long double: flerpl \
    )


#define lerp(v0, v1, t) lerp_fn_3(v0, v1, t)(v0, v1, t)

#endif // LERP_H_

// References:
// https://en.wikipedia.org/wiki/C11_%28C_standard_revision%29
// https://gcc.gnu.org/wiki/C11Status
// http://www.robertgamble.net/2012/01/c11-generic-selections.html
// https://stackoverflow.com/questions/9804371/syntax-and-sample-usage-of-generic-in-c11
