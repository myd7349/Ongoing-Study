#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H


#include <QtCore/QPointF>
#include <QtCore/QSharedPointer>


class QPen;
class QBrush;
class QStylePainter;

struct BezierCurve
{
    enum Type
    {
        Linear = 0,
        Quadratic = 1,
        Cubic = 2,
    };

    QPointF start;
    QPointF end;
    QPointF c1;
    QPointF c2;

    Type getType() const
    {
        return static_cast<Type>(
            static_cast<int>(!c1.isNull()) + static_cast<int>(!c2.isNull()));
    }

    void draw(QStylePainter &painter);
};

using BezierCurveSafePtr = QSharedPointer<BezierCurve>;

#endif
