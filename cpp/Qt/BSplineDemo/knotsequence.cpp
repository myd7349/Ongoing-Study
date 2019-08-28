#include "knotsequence.h"

#include <QtCore/QtMath>
#include <QtGui/QPainterPath>
#include <QtWidgets/QStylePainter>

#include <tinysplinecpp.h>

#include "../../DesignPatterns/Singleton.hpp"


constexpr qreal R = 5.0f;


static void DrawPoint(QStylePainter &painter, const QPointF &pt)
{
    QPainterPath pointPath;

    pointPath.addEllipse(pt, 2.0f, 2.0f);
    painter.fillPath(pointPath, QBrush(Qt::black));
}


static void DrawPoint(QStylePainter &painter, qreal x, qreal y)
{
    DrawPoint(painter, QPointF(x, y));
}


static void DrawControlPoint(QStylePainter &painter, const QPointF &pt)
{
    painter.save();

    QPen pen(QBrush(Qt::red), 1.0f);
    painter.setPen(pen);

    qreal sideLength = qSqrt(R * R + R * R);
    QRectF rect(-sideLength / 2, -sideLength / 2, sideLength, sideLength);

    painter.translate(pt);
    painter.rotate(45.0f);

    painter.drawRect(rect);
    painter.fillRect(rect, QBrush(QColor(255, 255, 100, 200)));

    painter.restore();
}


static void DrawControlPoint(QStylePainter &painter, qreal x, qreal y)
{
    DrawControlPoint(painter, QPointF(x, y));
}


void KnotSequence::draw(QStylePainter &painter)
{
    auto &sequence = Singleton<KnotSequence>::GetInstance();
    if (sequence.empty())
        return;

    std::vector<tinyspline::real> knots;
    knots.reserve(sequence.size() * 2);

    for (const auto &pt : sequence)
    {
        DrawPoint(painter, pt);

        knots.push_back(pt.x());
        knots.push_back(pt.y());
    }

    if (sequence.size() < 2)
        return;

    auto bSpline = tinyspline::Utils::interpolateCubic(&knots, 2);
    auto controlPoints = bSpline.controlPoints();

    Q_ASSERT(controlPoints.size() % 8 == 0);

    QPainterPath path;

    for (KnotSequence::size_type i = 1; i < sequence.size(); ++i)
    {
        path.moveTo(knots[(i - 1) * 2], knots[(i - 1) * 2 + 1]);
        path.cubicTo(
            controlPoints[(i - 1) * 8 + 2], controlPoints[(i - 1) * 8 + 3],
            controlPoints[(i - 1) * 8 + 4], controlPoints[(i - 1) * 8 + 5],
            controlPoints[(i - 1) * 8 + 6], controlPoints[(i - 1) * 8 + 7]
        );

        DrawPoint(painter, knots[(i -1) * 2], knots[(i - 1) * 2 + 1]);
        DrawPoint(painter, knots[i * 2], knots[i * 2 + 1]);
        
        DrawControlPoint(painter, controlPoints[(i - 1) * 8 + 2], controlPoints[(i - 1) * 8 + 3]);
        DrawControlPoint(painter, controlPoints[(i - 1) * 8 + 4], controlPoints[(i - 1) * 8 + 5]);
    }

    painter.drawPath(path);
}
