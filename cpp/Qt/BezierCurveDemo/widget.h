// 2017-07-15T17:35+08:00
#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>

#include "BezierCurve.h"
#include "MouseActionBase.hpp"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    QPixmap render();

    BezierCurveSafePtr bezierCurve;
    MouseActionList mouseActionList;
};

#endif // WIDGET_H
