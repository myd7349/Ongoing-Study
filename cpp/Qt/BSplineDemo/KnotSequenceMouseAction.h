#pragma once

#include "../BezierCurveDemo/MouseActionBase.hpp"


class KnotSequenceMouseAction : public MouseActionBase
{
public:
    bool mouseDoubleClickEvent(QObject *sender, QMouseEvent *event) override;
};
