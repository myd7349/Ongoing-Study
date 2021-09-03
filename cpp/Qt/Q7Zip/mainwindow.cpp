#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStylePainter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Q7z");

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            QSize(800, 640),
            qApp->primaryScreen()->availableGeometry()
        )
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}
