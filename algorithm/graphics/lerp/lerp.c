#include "lerp.h"

#ifndef NDEBUG
# include <stdio.h>

# include "../../algutils.h"
#endif


#if 0

// Generic selection is a primary expression.

#define LERP_T(T) \
T lerp_fn_1((T)0)(T v0, T v1, T t) \
{ \
    return (1 - t) * v0 + t * v1; \
}


LERP_T(float)
LERP_T(double)
LERP_T(long double)

LERP_T(int)
LERP_T(long)
LERP_T(long long)

#else

#if 0

// ???
#define LERP_T(T, fn) \
T fn(T v0, T v1, T t) \
{ \
#if 0 \
    assert(t >= 0.0 - 1e-7 && t <= 1.0 + 1e-7); \
#endif \
    \
#ifndef NDEBUG \
    printf("Call function " STR(fn) ": "); \
#endif \
    return (1 - t) * v0 + t * v1; \
}

#else

#ifndef NDEBUG

#define LERP_T(T, fn) \
T fn(T v0, T v1, T t) \
{ \
    printf("Call function " STR(fn) ": "); \
    return (1 - t) * v0 + t * v1; \
}

#else

#define LERP_T(T, fn) \
T fn(T v0, T v1, T t) \
{ \
    return (1 - t) * v0 + t * v1; \
}

#endif

#endif

LERP_T(float, flerpf)
LERP_T(double, flerp)
LERP_T(long double, flerpl)

#undef lerp

LERP_T(int, lerp)
LERP_T(long, llerp)
LERP_T(long long, lllerp)

#endif


// References:
// https://github.com/komorra/NodeEditorWinforms/blob/master/NodeEditor/NodesGraph.cs#L132
// https://en.wikipedia.org/wiki/Linear_interpolation
// https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Linear_B.C3.A9zier_curves
