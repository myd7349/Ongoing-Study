#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QPixmap>
#include <QtWidgets/QMainWindow>

#include "../BezierCurveDemo/MouseActionBase.hpp"


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
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap render();

    Ui::MainWindow *ui;

    MouseActionList mouseActionList_;
};

#endif // MAINWINDOW_H
