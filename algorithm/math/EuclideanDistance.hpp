// 2017-11-30T12:39+08:00
// Winter is coming!

#ifndef EUCLIDEAN_DISTANCE_HPP_
#define EUCLIDEAN_DISTANCE_HPP_

#include <cmath>


template <typename T>
inline T SquaredDistance2(T x1, T y1, T x2, T y2)
{
    T dx = x2 - x1;
    T dy = y2 - y1;
    return dx * dx + dy * dy;
}


template <typename T>
inline T Distance2(T x1, T y1, T x2, T y2)
{
    return std::sqrt(SquaredDistance2(x1, y1, x2, y2));
}


template <typename PointT, typename T = typename PointT::value_type>
inline T SquaredDistance2(const PointT &p1, const PointT &p2)
{
    return SquaredDistance2<T>(p1.x, p1.y, p2.x, p2.y);
}


template <typename PointT, typename T = typename PointT::value_type>
inline T Distance2(const PointT &p1, const PointT &p2)
{
    return std::sqrt(SquaredDistance2<PointT, T>(p1, p2));
}


#ifdef QT_VERSION
# include <QtCore/QPoint>
# include <QtCore/QPointF>

template <>
inline int SquaredDistance2<QPoint, int>(const QPoint &p1, const QPoint &p2)
{
    return SquaredDistance2(p1.x(), p1.y(), p2.x(), p2.y());
}

template <>
inline qreal SquaredDistance2<QPointF, qreal>(const QPointF &p1, const QPointF &p2)
{
    return SquaredDistance2(p1.x(), p1.y(), p2.x(), p2.y());
}
#endif

#endif // EUCLIDEAN_DISTANCE_HPP_

// References:
// https://en.wikipedia.org/wiki/Euclidean_distance
