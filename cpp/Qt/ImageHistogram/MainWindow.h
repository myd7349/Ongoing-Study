// 2016-08-30T08:50+08:00
// A Qt clone of a sample with a same name in DynamicDataDisplay(a.k.a D3).
// http://dynamicdatadisplay.codeplex.com/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QImage>
#include <QtWidgets/QMainWindow>

namespace QtCharts {
class QChartView;
}

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void centerWindowOnScreen();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void onOpenImage();
    void onTriggleLogMapping();

private:
    void initializeMainMenu();
    void initializeChartView();

    void openImage(const QString &fileName);
    void processImage(QImage &image);
    void refreshPictureBox();

    QImage currentImage;
    QLabel *pictureBox = nullptr;
    QtCharts::QChartView *chartView = nullptr;
    bool useLogMapping = false;
};

#endif // MAINWINDOW_H

// References:
// http://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-example.html
// http://doc.qt.io/qt-5/qtcharts-splinechart-example.html
// http://doc.qt.io/qt-5/qtcharts-index.html
// http://stackoverflow.com/questions/8211982/qt-resizing-a-qlabel-containing-a-qpixmap-while-keeping-its-aspect-ratio
// https://wiki.qt.io/How_to_Center_a_Window_on_the_Screen
//
// http://www.jianshu.com/p/88fa240f19b7
// http://neicole.blog.51cto.com/5621716/967329
