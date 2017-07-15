#include "BezierCurve.h"

#include <QtGui/QPainterPath>
#include <QtWidgets/QStylePainter>


void BezierCurve::draw(QStylePainter &painter)
{
    QPainterPath path;
    path.moveTo(start);

    switch (getType()) {
    case Linear: path.lineTo(end); break;
    case Quadratic: path.quadTo(c1.isNull() ? c2 : c1, end); break;
    case Cubic: path.cubicTo(c1, c2, end); break;
    default: Q_ASSERT(false); break;
    }

    painter.drawPath(path);
}
