#include "mainwindow.h"

#include <QtGui/QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent */*event*/)
{
    // http://www.zhihu.com/question/24424379
    QPainter painter(this);
    QString str = QString::fromWCharArray(L"\x200E" L"ENGlish (UK)" L"\x200E");

    painter.setLayoutDirection(Qt::RightToLeft);
    painter.drawText(rect(),Qt::AlignLeft | Qt::AlignVCenter, str);
}
