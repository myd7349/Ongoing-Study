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


template <typename PointT>
inline PointT MidPoint(const PointT &p1, const PointT &p2)
{
    using T = typename PointT::value_type;
    return PointT(static_cast<T>((p1.x + p2.x) / 2.0), static_cast<T>((p1.y + p2.y) / 2.0));
}


template <typename PointT, typename PointContainer>
void RecursiveSubdivisionQuadraticBezierImpl(const PointT &P0, const PointT &P1, const PointT &P2, PointContainer &points)
{
}


template <typename PointT, typename PointContainer>
void RecursiveSubdivisionCubicBezierImpl(const PointT &P0, const PointT &P1,
    const PointT &P2, const PointT &P3, PointContainer &points,
    double distanceTolerance = 0.025)
{
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

    RecursiveSubdivisionCubicBezierImpl(P0, P01, P012, P0123, points, distanceTolerance);
    RecursiveSubdivisionCubicBezierImpl(P0123, P123, P23, P3, points, distanceTolerance);
}


template <typename PointContainer>
inline void RecursiveSubdivisionBezier(const PointContainer &controlPoints, PointContainer &points)
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
        RecursiveSubdivisionQuadraticBezierImpl<PointT, PointContainer>(P0, P1, P2, points);
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
        RecursiveSubdivisionCubicBezierImpl<PointT, PointContainer>(P0, P1, P2, P3, points);
        points.push_back(P3);
    }
        break;
    default: assert(false); break;
    }
}


#endif // DE_CASTELJAU_H_

// References:
// https://en.wikipedia.org/wiki/B%C3%A9zier_curve
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
