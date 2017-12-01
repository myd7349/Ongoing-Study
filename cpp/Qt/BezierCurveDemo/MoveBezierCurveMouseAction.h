// 2017-12-01T18:06+08:00
#ifndef MOVE_BEZIER_CURVE_MOUSE_ACTION_H
#define MOVE_BEZIER_CURVE_MOUSE_ACTION_H

#include <QtCore/QPointF>

#include "MouseActionBase.hpp"


class MoveBezierCurveMouseAction : public MouseActionBase
{
public:
    virtual bool mousePressEvent(QObject *sender, QMouseEvent *event);

    virtual bool mouseReleaseEvent(QObject *sender, QMouseEvent *event);

    virtual bool mouseMoveEvent(QObject *sender, QMouseEvent *event);

private:
    bool isMoving = false;
    QPointF prevPosition;
};

#endif
