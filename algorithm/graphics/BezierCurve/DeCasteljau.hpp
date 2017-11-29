// 2017-11-29T08:54+08:00
// A recursive subdivision method for rasterizing a Bézier curve.

#ifndef DE_CASTELJAU_H_
#define DE_CASTELJAU_H_

#include <cassert>
#include <ctgmath>


template <typename T>
struct Point
{
    typedef T value_type;

    Point(T x_ = T(), T y_ = T()) : x(x_), y(y_)
    {
    }

    value_type x;
    value_type y;
};


const int CurveRecursionLimit = 32;


template <typename PointT>
inline PointT MidPoint(const PointT &p1, const PointT &p2)
{
    using T = typename PointT::value_type;
    return PointT(static_cast<T>((p1.x + p2.x) / 2.0), static_cast<T>((p1.y + p2.y) / 2.0));
}


template <typename PointT, typename PointContainer>
void RecursiveSubdivisionCubicBezierImpl(const PointT &P0, const PointT &P1,
    const PointT &P2, const PointT &P3, PointContainer &points,
    double distanceTolerance, unsigned level = 0)
{
    if (level > CurveRecursionLimit)
        return;

    // Calculate all the mid-points of the line segments
    PointT P01 = MidPoint(P0, P1);
    PointT P12 = MidPoint(P1, P2);
    PointT P23 = MidPoint(P2, P3);
    PointT P012 = MidPoint(P01, P12);
    PointT P123 = MidPoint(P12, P23);
    PointT P0123 = MidPoint(P012, P123);

    // Suppose we have:
    // A point specified by (x0, y0)
    // A line specified by two points (x1, y1), (x2, y2)
    // From [3], we know the Point-Line Distance is:
    /*
     *      |(x2-x1)(y1-y0) - (y2-y1)(x1-x0)|
     * d = -----------------------------------
     *         sqrt((x2-x1)^2 + (y2-y1)^2)
    */
    // Then, we can get the distance between point P1 and line P0-P3
    /*
     *       |(P3.x-P0.x)(P0.y-P1.y) - (P3.y-P0.y)(P0.x-P1.x)|
     * d1 = --------------------------------------------------
     *           sqrt((P3.x-P0.x)^2 + (P3.y-P0.y)^2)
    */
    // In the same way, we can get the distance between point P2 and line P1-P3
    /*
     *       |(P3.x-P0.x)(P0.y-P2.y) - (P3.y-P0.y)(P0.x-P2.x)|
     * d2 = --------------------------------------------------
     *           sqrt((P3.x-P0.x)^2 + (P3.y-P0.y)^2)
    */
    // If d1 + d2 is very small, we say that the curve is almost flat.
    //
    double dx = P3.x - P0.x;
    double dy = P3.y - P0.y;

    double d1 = std::fabs((P1.x - P3.x) * dy - (P1.y - P3.y) * dx);
    double d2 = std::fabs((P2.x - P3.x) * dy - (P2.y - P3.y) * dx);

    if ((d1 + d2) * (d1 + d2) < distanceTolerance * (dx * dx + dy * dy))
    {
        points.push_back(P0123);
        return;
    }

    RecursiveSubdivisionCubicBezierImpl(P0, P01, P012, P0123, points, distanceTolerance,
        level + 1);
    RecursiveSubdivisionCubicBezierImpl(P0123, P123, P23, P3, points, distanceTolerance,
        level + 1);
}


// In GDI/GDI+, the PolyBezier/DrawBezier functions draw cubic Bézier curves
// by using the endpoints and control points specified by the parameters.
// The first curve is drawn from the first point to the fourth point by using the
// second and third points as control points. Each subsequent curve in the
// sequence needs exactly three more points: the ending point of the previous
// curve is used as the starting point, the next two points in the sequence
// are control points, and the third is the ending point.
// See also: PolyDraw, PolyBezierTo

// In WPF, there is a QuadraticBezierTo method.

template <typename PointT, typename PointContainer>
void RecursiveSubdivisionQuadraticBezierImpl(const PointT &P0, const PointT &P1, const PointT &P2,
    PointContainer &points, double distanceTolerance)
{
    // Can we simply implement RecursiveSubdivisionQuadraticBezierImpl like this?
    //RecursiveSubdivisionCubicBezierImpl(P0, P1, P1, P2, points, distanceTolerance);
    // No! We can't.
    // When P1 and P2 are the same point, we can not get:
    // B(t) = (1-t)^2*P0 + 2*(1-t)*t*P1 + t^2*P2
    // from:
    // B(t) = (1-t)^3*P0 + 3*(1-t)^2*t*P1 + 3*(1-t)*t^2*P2 + t^3*P3
    // Or you may confirm it by uncommenting line 42, 43 in BezierCurve.cpp.
    //
    // Wait! If you really want to draw quadratic Bezier curve with a function
    // that draws Cubic Bezier curve, you have to do some convert manually.
    /*
    >Any quadratic spline can be expressed as a cubic (where the cubic term is zero).
    The end points of the cubic will be the same as the quadratic's.

    CP0 = QP0
    CP3 = QP2

    The two control points for the cubic are:

    CP1 = QP0 + 2/3 *(QP1-QP0)
    CP2 = QP2 + 2/3 *(QP1-QP2)
    */
    // See [4] for detail.
    // Or you may take a look at:
    // Ongoing-Study/python/pythonnet/DrawQuadraticBezierCurve.pyw
}


template <typename PointContainer>
inline void RecursiveSubdivisionBezier(const PointContainer &controlPoints, PointContainer &points,
    double distanceTolerance = 0.5 * 0.5 // See [1]
    )
{
    using PointT = typename PointContainer::value_type;

    points.clear();

    switch (controlPoints.size())
    {
    case 2:
    {
        points.resize(2);
        points[0] = controlPoints[0];
        points[1] = controlPoints[1];
    }
        break;
    case 3:
    {
        const PointT &P0 = controlPoints[0];
        const PointT &P1 = controlPoints[1];
        const PointT &P2 = controlPoints[2];

        points.push_back(P0);
        RecursiveSubdivisionQuadraticBezierImpl<PointT, PointContainer>(P0, P1, P2, points, distanceTolerance);
        points.push_back(P2);
    }
        break;
    case 4:
    {
        const PointT &P0 = controlPoints[0];
        const PointT &P1 = controlPoints[1];
        const PointT &P2 = controlPoints[2];
        const PointT &P3 = controlPoints[3];

        points.push_back(P0);
        RecursiveSubdivisionCubicBezierImpl<PointT, PointContainer>(P0, P1, P2, P3, points, distanceTolerance);
        points.push_back(P3);
    }
        break;
    default: assert(false); break;
    }
}


#endif // DE_CASTELJAU_H_

// References:
// [0] https://en.wikipedia.org/wiki/B%C3%A9zier_curve
/*
>The simplest method for scan converting (rasterizing) a Bézier curve is to
evaluate it at many closely spaced points and scan convert the approximating
sequence of line segments. However, this does not guarantee that the rasterized
output looks sufficiently smooth, because the points may be spaced too far apart.
Conversely it may generate too many points in areas where the curve is close to
linear. A common adaptive method is recursive subdivision, in which a curve's control
points are checked to see if the curve approximates a straight line to within a
small tolerance. If not, the curve is subdivided parametrically into two segments,
0 ≤ t ≤ 0.5 and 0.5 ≤ t ≤ 1, and the same procedure is applied recursively to each half.
*/
// [1] http://antigrain.com/research/adaptive_bezier/index.html
// [2] https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-sub.html
// [3] http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
// [4] https://stackoverflow.com/questions/3162645/convert-a-quadratic-bezier-to-a-cubic
