#include "BezierCurve.h"

#include <QtGui/QPainterPath>
#include <QtGui/QPen>
#include <QtWidgets/QStylePainter>


void BezierCurve::draw(QStylePainter &painter)
{
    Type type = getType();
    if (type == Invalid)
        return;

    QPen pen(QBrush(Qt::blue), 4.0f);
    painter.setPen(pen);

    QPainterPath path;
    path.moveTo(*start());

    switch (type) {
    case Linear: path.lineTo(*end()); break;
    case Quadratic: path.quadTo(c1() == nullptr ? *c2() : *c1(), *end()); break;
    case Cubic: path.cubicTo(*c1(), *c2(), *end()); break;
    default: Q_ASSERT(false); break;
    }

    painter.drawPath(path);
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
        "You can remove a point by double clicking on it.\n"
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

    pen.setColor(Qt::red);
    painter.setPen(pen);

    if (c1() != nullptr)
        painter.drawEllipse(*c1(), R, R);

    if (c2() != nullptr)
        painter.drawEllipse(*c2(), R, R);
}
