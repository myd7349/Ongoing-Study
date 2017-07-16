#include "AdjustBezierCurveMouseAction.h"

#include "../../DesignPatterns/Singleton.h"
#include "BezierCurve.h"


bool AdjustBezierCurveMouseAction::mousePressEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);

    Q_ASSERT(event != nullptr);
    if (event->button() != Qt::LeftButton)
        return false;

    auto bezierCurve = Singleton<DecoratedBezierCurve>::GetInstancePtr();

    point = bezierCurve->hitTest(event->pos());
    return false;
}

bool AdjustBezierCurveMouseAction::mouseReleaseEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);
    Q_UNUSED(event);

    if (point != nullptr)
        point = nullptr;

    return false;
}

bool AdjustBezierCurveMouseAction::mouseMoveEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);

    Q_ASSERT(event != nullptr);

    if (point != nullptr)
    {
        *point = event->pos();
        return true;
    }

    return false;
}
