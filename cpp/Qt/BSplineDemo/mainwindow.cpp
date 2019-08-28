#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QPixmapCache>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QStylePainter>

#include "../../DesignPatterns/Singleton.hpp"
#include "knotsequence.h"
#include "KnotSequenceMouseAction.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("B-Spline Demo");

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            QSize(800, 640),
            qApp->desktop()->availableGeometry()
        )
    );

    mouseActionList_.pushBack(QSharedPointer<KnotSequenceMouseAction>::create());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (mouseActionList_.mouseDoubleClickEvent(this, event))
        repaint();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (mouseActionList_.mousePressEvent(this, event))
        repaint();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStylePainter painter(this);
    painter.drawPixmap(0, 0, render());
}


QPixmap MainWindow::render()
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

    Singleton<KnotSequence>::GetInstance().draw(painter);

    return pixmap;
}
