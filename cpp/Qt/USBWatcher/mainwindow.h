// 2014-05-14T16:36:14+08:00
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
