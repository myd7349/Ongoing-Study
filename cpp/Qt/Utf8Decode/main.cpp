// 2014-04-24T13:49+08:00
#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>
#include <QTextCodec>

#include <iostream>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef Q_OS_WIN
    ::SetConsoleCP(437);
#endif

#if 0
    QString reply = QString::fromUtf8("\u8d26\u53f7\u4e0d\u5b58\u5728");
    std::cout << qPrintable(reply) << std::endl;
#else
    // QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    qDebug() << QString::fromUtf8("\u8d26\u53f7\u4e0d\u5b58\u5728");
#endif
    return a.exec();
}
