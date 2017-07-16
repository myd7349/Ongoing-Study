#ifndef ADJUST_BEZIER_CURVE_MOUSE_ACTION_H
#define ADJUST_BEZIER_CURVE_MOUSE_ACTION_H

#include "MouseActionBase.hpp"


class QPointF;

class AdjustBezierCurveMouseAction : public MouseActionBase
{
public:
    virtual bool mousePressEvent(QObject *sender, QMouseEvent *event);

    virtual bool mouseReleaseEvent(QObject *sender, QMouseEvent *event);

    virtual bool mouseMoveEvent(QObject *sender, QMouseEvent *event);

private:
    QPointF *point = nullptr;
};

#endif
