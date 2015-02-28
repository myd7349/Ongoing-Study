#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class QAction;
class QMenu;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onShowOrHideColumn(QAction *action);

private:
    QTableWidget *stuInfoWidget;

    QMenu *mainMenu;
};

#endif // MAINWINDOW_H
