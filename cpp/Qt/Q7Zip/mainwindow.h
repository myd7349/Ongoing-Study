#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>


class Q7Zip;


namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void extractArchive();
    void createArchive();

private:
    Ui::MainWindow *ui;

    Q7Zip *q7zip_;
};

#endif // MAINWINDOW_H
