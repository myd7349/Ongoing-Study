#include <QApplication>
#include <QLocale>
#include <QPushButton>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << QLocale::system().name();

    QTranslator translator;
#if 1
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "hellotr_" + QLocale(locale).name();
        qDebug() << "Trying to load " << baseName << "...";
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        } else {
            qDebug() << "Failed to load " << baseName;
        }
    }
#else
    if (translator.load("hellotr_zh_CN"))
        a.installTranslator(&translator);
#endif

    QPushButton hello(QPushButton::tr("Hello, world!"));
    hello.resize(160, 40);
    hello.show();

    return a.exec();
}


// References:
// [Qt Linguist Manual: Developers](https://doc.qt.io/qt-5/linguist-programmers.html)
// [Qt Linguist Examples: hellotr](https://doc.qt.io/qt-5/qtlinguist-hellotr-example.html)
