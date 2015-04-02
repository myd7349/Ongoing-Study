// 2014-03-05T10:45+08:00
// zhidao.baidu.com/question/710994286804159085.html
#include <QCoreApplication>
#include <QHostAddress>

#include "serverobj.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ServerObj server;
    if (!server.listen(QHostAddress::Any, 7349)) {
        return 1;
    }

    return app.exec();
}
