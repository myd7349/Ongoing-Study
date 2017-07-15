// 2017-07-15T17:35+08:00
#include <QtWidgets/QApplication>

#include "widget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget widget;
    widget.show();

    return app.exec();
}
