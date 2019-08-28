#include "knotsequence.h"

#include <QtCore/QtMath>
#include <QtWidgets/QStylePainter>

#include <tinysplinecpp.h>

#include "../../DesignPatterns/Singleton.hpp"


constexpr qreal R = 4.0f;


static void DrawKnot(QStylePainter &painter, const QPointF &pt)
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


static void DrawKnot(QStylePainter &painter, qreal x, qreal y)
{
    DrawKnot(painter, QPointF(x, y));
}


void KnotSequence::draw(QStylePainter &painter)
{
    auto &sequence = Singleton<KnotSequence>::GetInstance();
    
    std::vector<tinyspline::real> knots;
    knots.reserve(sequence.size() * 2);

    for (const auto &pt : sequence)
    {
        DrawKnot(painter, pt);

        knots.push_back(pt.x());
        knots.push_back(pt.y());
    }

    auto bSpline = tinyspline::Utils::interpolateCubic(&knots, 2);

    knots = bSpline.knots();

    Q_ASSERT(knots.size() % 2 == 0);

    for (std::vector<tinyspline::real>::size_type i = 0; i < knots.size(); i += 2)
    {
        DrawKnot(painter, knots[i], knots[i + 1]);
    }
}
