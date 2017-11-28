#include "lerp.h"


#if 0

// Generic selection is a primary expression.

#define LERP_T(T) \
T lerp_fn((T)0)(T v0, T v1, T t) \
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

#define LERP_T(T, fn) \
T fn(T v0, T v1, T t) \
{ \
    return (1 - t) * v0 + t * v1; \
}

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
