#include "BezierCurve.h"

#include <algorithm>

#include <QtGui/QPen>
#include <QtMath>
#include <QtWidgets/QStylePainter>

#include "../../../algorithm/graphics/BezierCurve/DeCasteljau.hpp"
#include "../../../algorithm/graphics/lerp/lerp.h"


void BezierCurve::draw(QStylePainter &painter)
{
    Type type = getType();
    if (type == Invalid)
        return;

    painter.save();

    QColor penColor(Qt::blue);
    penColor.setAlpha(100);

    QPen pen(penColor, 10.0f);
    painter.setPen(pen);

    QPainterPath path;
    path.moveTo(*start());

    switch (type) {
    case Linear: path.lineTo(*end()); break;
    case Quadratic:
        // Can we simply implement RecursiveSubdivisionQuadraticBezierImpl like this?
        //RecursiveSubdivisionCubicBezierImpl(P0, P1, P1, P2, points, distanceTolerance);
        // No! We can't.
        // When P1 and P2 are the same point, we can not get:
        // B(t) = (1-t)^2*P0 + 2*(1-t)*t*P1 + t^2*P2
        // from:
        // B(t) = (1-t)^3*P0 + 3*(1-t)^2*t*P1 + 3*(1-t)*t^2*P2 + t^3*P3
        // Or you may confirm it by uncommenting line 42, 43 below:
        path.quadTo(c1() == nullptr ? *c2() : *c1(), *end());
        //path.moveTo(*start());
        //path.cubicTo(c1() == nullptr ? *c2() : *c1(), c1() == nullptr ? *c2() : *c1(), *end());
        //
        // Wait! If you really want to draw quadratic Bezier curve with a function
        // that draws Cubic Bezier curve, you have to do some convert manually.
        // See [4] in DeCasteljau.hpp for detail.
        break;
    case Cubic: path.cubicTo(*c1(), *c2(), *end()); break;
    default: Q_ASSERT(false); break;
    }

    painter.drawPath(path);

    pen.setColor(Qt::red);
    pen.setWidthF(1.0);
    painter.setPen(pen);

    const QVector<QPointF> &pointsOnCurve_ = points();
    for (QVector<QPointF>::size_type i = 1; i < pointsOnCurve_.size(); ++i)
        painter.drawLine(pointsOnCurve_[i - 1], pointsOnCurve_[i]);

    painter.restore();
}


#if 0
const QVector<QPointF> &BezierCurve::points(int maxPoints)
{
    pointsOnCurve.clear();

    Type type = getType();
    if (type == Invalid)
        return pointsOnCurve;

    if (maxPoints == -1)
        maxPoints = static_cast<int>(distance(*start(), *end()));

    if (maxPoints <= 0)
        maxPoints = 2;

    if (maxPoints > 0)
        pointsOnCurve.resize(maxPoints);

    qreal t = 0.0;
    qreal tStep = 1.0 / maxPoints;

    switch (type) {
    case Linear:
    {
        QPointF P0 = *start();
        QPointF P1 = *end();

        for (int i = 0; i < maxPoints; ++i)
        {
            pointsOnCurve[i].setX(flerp(P0.x(), P1.x(), t));
            pointsOnCurve[i].setY(flerp(P0.y(), P1.y(), t));
            t += tStep;
        }
    }
        break;
    case Quadratic:
    {
        QPointF P0 = *start();
        QPointF P1 = c1() == nullptr ? *c2() : *c1();
        QPointF P2 = *end();

        for (int i = 0; i < maxPoints; ++i)
        {
            qreal term0 = qPow(1.0 - t, 2.0);
            qreal term1 = 2.0 * (1.0 - t) * t;
            qreal term2 = t * t;

            pointsOnCurve[i].setX(term0 * P0.x() + term1 * P1.x() + term2 * P2.x());
            pointsOnCurve[i].setY(term0 * P0.y() + term1 * P1.y() + term2 * P2.y());

            t += tStep;
        }
    }
        break;
    case Cubic:
    {
        QPointF P0 = *start();
        QPointF P1 = *c1();
        QPointF P2 = *c2();
        QPointF P3 = *end();

        for (int i = 0; i < maxPoints; ++i)
        {
            qreal term0 = qPow(1.0 - t, 3.0);
            qreal term1 = 3.0 * qPow(1.0 - t, 2.0) * t;
            qreal term2 = 3.0 * (1.0 - t) * t * t;
            qreal term3 = qPow(t, 3.0);

            pointsOnCurve[i].setX(term0 * P0.x() + term1 * P1.x() + term2 * P2.x() + term3 * P3.x());
            pointsOnCurve[i].setY(term0 * P0.y() + term1 * P1.y() + term2 * P2.y() + term3 * P3.y());

            t += tStep;
        }
    }
        break;
    default: Q_ASSERT(false); break;
    }

    return pointsOnCurve;
}
#else
template <typename T>
inline Point<T> QPointFToPoint(const QPointF &point)
{
    return Point<T>(static_cast<T>(point.x()), static_cast<T>(point.y()));
}


template <typename T>
inline QPointF PointToQPointF(const Point<T> &point)
{
    return QPointF(static_cast<qreal>(point.x), static_cast<qreal>(point.y));
}


void RecursiveSubdivisionBezier(const QVector<QPointF> &controlPoints, QVector<QPointF> &points)
{
    QVector<Point<qreal>> Ps(controlPoints.size());
    std::transform(controlPoints.cbegin(), controlPoints.cend(), Ps.begin(), QPointFToPoint<qreal>);

    QVector<Point<qreal>> bezierCurve;
    RecursiveSubdivisionBezier(Ps, bezierCurve);

    points.resize(bezierCurve.size());
    std::transform(bezierCurve.cbegin(), bezierCurve.cend(), points.begin(), PointToQPointF<qreal>);
}


const QVector<QPointF> &BezierCurve::points(int maxPoints)
{
    Q_UNUSED(maxPoints);

    pointsOnCurve.clear();

    Type type = getType();
    if (type == Invalid)
        return pointsOnCurve;

    QVector<QPointF> Ps = controlPoints;

    switch (type)
    {
    case Quadratic:
        // controlPoints: start, end, P1
        // Ps: start, P1, end
        std::swap(Ps[1], Ps[2]);
        break;
    case Cubic:
        // controlPoints: start, end, P1, P2
        // Ps: start, P1, P2, end
        std::swap(Ps[1], Ps[2]);
        std::swap(Ps[2], Ps[3]);
        break;
    default: break;
    }

    RecursiveSubdivisionBezier(Ps, pointsOnCurve);

    return pointsOnCurve;
}
#endif


// I think the control point shown in:
// https://www.zhihu.com/question/64330190
// looks nice!
void DecoratedBezierCurve::drawPointMarker(QStylePainter &painter, const QPointF &pt)
{
    painter.save();

    QPen pen(QBrush(Qt::red), 1.0f);
    painter.setPen(pen);

    qreal sideLength = qSqrt(R * R + R * R);
    QRectF rect(-sideLength / 2, -sideLength / 2, sideLength, sideLength);

    painter.translate(pt); // [1]
    painter.rotate(45.0f);

    painter.drawRect(rect);
    painter.fillRect(rect, QBrush(QColor(255, 255, 100, 200)));

    //painter.resetTransform();

    painter.restore();
}


void DecoratedBezierCurve::draw(QStylePainter &painter)
{
    BezierCurve::draw(painter);

    const int pointsCount =
        static_cast<int>(start() != nullptr) +
        static_cast<int>(end() != nullptr) +
        static_cast<int>(c1() != nullptr) +
        static_cast<int>(c2() != nullptr);

    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);

    const char *tips[] = {
        "Double click in the drawing area to add the [Start] point...",
        "Good! Now add the [End] point in the same way...\n"
        "You can remove a point by double clicking the right mouse button.\n"
        "You can drag a point by holding the left mouse button.\n",
        "Congratulations! You have just created a linear Bézier curve.\n"
        "You can also add at most 2 control points in the same way.",
        "Congratulations! You have just created a quadratic Bézier curve.",
        "Congratulations! You have just created a cubic Bézier curve.",
    };

    painter.drawText(QRectF(10.0f, 22.0f, 800.0f, 200.0f),
        Qt::TextWordWrap | Qt::TextDontClip, tips[pointsCount]);

    QPen pen(QBrush(Qt::black), 1.0f);
    painter.setPen(pen);

    if (start() != nullptr)
        painter.drawEllipse(*start(), R, R);

    if (end() != nullptr)
        painter.drawEllipse(*end(), R, R);

    if (c1() != nullptr) {
        painter.drawLine(*start(), *c1());
        if (c2() == nullptr)
            painter.drawLine(*end(), *c1());

        drawPointMarker(painter, *c1());
    }

    if (c2() != nullptr) {
        if (c1() == nullptr)
            painter.drawLine(*start(), *c2());
        painter.drawLine(*end(), *c2());

        drawPointMarker(painter, *c2());
    }
}

// References:
// [1][Rotate rectangle around its center](https://stackoverflow.com/questions/8586088/rotate-rectangle-around-its-center)
// [2][Subdividing a Bézier Curve](https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-sub.html)
// [3][Adaptive Subdivision of Bezier Curves](http://antigrain.com/research/adaptive_bezier/index.html)
