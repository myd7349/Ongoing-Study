// 2014-07-15T17:34+08:00
// http://zhidao.baidu.com/question/199168895602898645.html
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QTextStream>

#include <iomanip>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString num("1234567890");
    double d = num.toDouble();

    // QTextStream 定义了一些manipulators
    qDebug() << Qt::fixed << qSetRealNumberPrecision(0) << d << Qt::endl;
    qDebug() << QString::number(d, 'f', 0);

    QTextStream os(stderr);
    os << Qt::fixed; // os.setRealNumberNotation(QTextStream::FixedNotation);
    os.setRealNumberPrecision(0);
    os << d << '\n';
    os.flush(); // Why stderr still need to flush?

    std::cout << d << std::endl;
    std::cout << std::fixed << std::setprecision(0)
              << d << std::endl;

    return a.exec();
}
