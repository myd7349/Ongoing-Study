#include <QApplication>
#include <QtCore/QVector>
#include <QtWidgets/QMainWindow>

#include <qcustomplot.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto customPlot = new QCustomPlot;

    QVector<double> x(101), y(101);
    for (int i = 0; i < 101; ++i)
    {
        x[i] = i / 50.0 - 1; // x goes from -1 to 1
        y[i] = x[i] * x[i]; // let's plot a quadratic function
    }

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

    QMainWindow mainWindow;
    mainWindow.setGeometry(100, 100, 640, 480);
    mainWindow.layout()->addWidget(customPlot);
    mainWindow.show();
    
    return app.exec();
}


// References:
// https://www.qcustomplot.com/index.php/tutorials/basicplotting
