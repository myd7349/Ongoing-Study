#include "widget.h"

#include <QtGui/QPixmapCache>
#include <QtWidgets/QStylePainter>

#include "AddBezierCurveMouseAction.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mouseActionList.pushBack(QSharedPointer<AddBezierCurveMouseAction>::create());
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStylePainter painter(this);
    painter.drawPixmap(0, 0, render());
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (mouseActionList.mousePressEvent(this, event))
        repaint();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (mouseActionList.mouseReleaseEvent(this, event))
        repaint();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseActionList.mouseMoveEvent(this, event))
        repaint();
}

QPixmap Widget::render()
{
    int w = geometry().width();
    int h = geometry().height();

    QString key = QString("%1,%2").arg(w).arg(h);

    QPixmap pixmap;
    if (!QPixmapCache::find(key, pixmap))
    {
        pixmap = QPixmap(w, h);
        QPixmapCache::insert(key, pixmap);
    }

    QRectF rect(0, 0, w, h);

    QStylePainter painter(&pixmap, this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect, Qt::white);

    return pixmap;
}

// References:
// [Fast and Flicker-Free](https://doc.qt.io/archives/qq/qq06-flicker-free.html)
// [Optimizing with QPixmapCache](http://doc.qt.io/archives/qq/qq12-qpixmapcache.html)
// [When does a Qt widget get a paintEvent?](https://stackoverflow.com/questions/11645667/when-does-a-qt-widget-get-a-paintevent)
