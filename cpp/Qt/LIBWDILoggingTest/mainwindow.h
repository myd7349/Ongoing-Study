#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private slots:
    void tick();

private:
    QListWidget *listWidget = nullptr;
};

#endif // MAINWINDOW_H
