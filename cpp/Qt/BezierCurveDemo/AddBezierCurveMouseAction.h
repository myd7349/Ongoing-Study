#ifndef ADD_BEZIER_CURVE_MOUSE_ACTION_H
#define ADD_BEZIER_CURVE_MOUSE_ACTION_H

#include "MouseActionBase.hpp"


class AddBezierCurveMouseAction : public MouseActionBase
{
public:
    virtual bool mouseDoubleClickEvent(QObject *sender, QMouseEvent *event);
};

#endif
