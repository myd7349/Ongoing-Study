#ifndef ADD_BEZIER_CURVE_MOUSE_ACTION_H
#define ADD_BEZIER_CURVE_MOUSE_ACTION_H

#include "MouseActionBase.hpp"


class AddBezierCurveMouseAction : public MouseActionBase
{
public:
    virtual bool mousePressEvent(QObject *sender, QMouseEvent *event);

    virtual bool mouseReleaseEvent(QObject *sender, QMouseEvent *event);

    virtual bool mouseMoveEvent(QObject *sender, QMouseEvent *event);
};

#endif
