#include "MoveBezierCurveMouseAction.h"

#include "../../DesignPatterns/Singleton.h"
#include "BezierCurve.h"


bool MoveBezierCurveMouseAction::mousePressEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);

    Q_ASSERT(event != nullptr);
    if (event->button() != Qt::LeftButton)
        return false;

    isMoving = Singleton<DecoratedBezierCurve>::GetInstancePtr()->isOnCurve(event->pos());
    if (isMoving)
        prevPosition = event->pos();

    return isMoving;
}

bool MoveBezierCurveMouseAction::mouseReleaseEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);
    Q_UNUSED(event);

    if (isMoving)
        isMoving = false;

    return false;
}

bool MoveBezierCurveMouseAction::mouseMoveEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);

    Q_ASSERT(event != nullptr);

    if (!isMoving)
        return false;

    QPointF newPosition = event->pos();
    Singleton<DecoratedBezierCurve>::GetInstancePtr()->offset(newPosition - prevPosition);
    prevPosition = newPosition;

    return true;
}
