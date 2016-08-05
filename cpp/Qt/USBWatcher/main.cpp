// 2014-05-14T16:36:14+08:00
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow win;
    win.show();

    return app.exec();
}
