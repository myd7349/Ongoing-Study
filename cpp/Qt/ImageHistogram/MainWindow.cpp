#include "MainWindow.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtCore/QStringList>

#include <QApplication>
#include <QtGui/QImageReader>

#include <QtWidgets/QAction>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStyle>

#include "../../common.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Image Histogram"));

    initializeMainMenu();

    pictureBox = new QLabel;
    pictureBox->setBackgroundRole(QPalette::Base);
    pictureBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    initializeChartView();

    auto horzLayout = new QHBoxLayout;
    horzLayout->addWidget(pictureBox);
    horzLayout->addWidget(chartView);
    horzLayout->setStretch(0, 1); // *
    horzLayout->setStretch(1, 3); // 3*

    auto widget = new QWidget();
    widget->setLayout(horzLayout);
    setCentralWidget(widget);

    setGeometry(100, 100, 640, 480);
}

MainWindow::~MainWindow()
{
}

void MainWindow::centerWindowOnScreen()
{
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    refreshPictureBox();
}

void MainWindow::onOpenImage()
{
    auto picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"),
        picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last(),
        tr("Image Files (*.png *.jpg *.bmp *.gif);;All Files (*.*)"));

    if (!fileName.isEmpty())
        openImage(fileName);
}

void MainWindow::onTriggleLogMapping()
{
    useLogMapping = !useLogMapping;
}

void MainWindow::initializeMainMenu()
{
    auto openImageAction = new QAction(tr("&Open image..."), this);
    openImageAction->setShortcut(QKeySequence::Open);
    connect(openImageAction, &QAction::triggered, this, &MainWindow::onOpenImage);

    auto triggleLogMappingAction = new QAction(tr("Use &Log mapping"), this);
    triggleLogMappingAction->setCheckable(true);
    connect(triggleLogMappingAction, &QAction::triggered, this, &MainWindow::onTriggleLogMapping);

    auto mainMenu = menuBar()->addMenu(tr("&Main"));
    mainMenu->addAction(openImageAction);
    mainMenu->addAction(triggleLogMappingAction);
}

void MainWindow::initializeChartView()
{
    if (chartView != nullptr)
        return;

    QFont titleFont(tr("Arial"), 12);

    auto *chart = new QtCharts::QChart;
    chart->setTitle(tr("Histogram of image"));
    chart->setMargins(QMargins(5, 2, 5, 5));
    chart->setTitleFont(titleFont);

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::openImage(const QString &fileName)
{
    QImageReader imageReader(fileName);
    imageReader.setAutoTransform(true);

    if (imageReader.read(&currentImage))
    {
#if 0
        resize(geometry().width(), geometry().height()); // emit a resize event
#else
        refreshPictureBox();
#endif

        processImage(currentImage);
    }
    else
    {
        QMessageBox::critical(this,
            QGuiApplication::applicationDisplayName(),
            tr("Failed to load image \"%1\": %2.").arg(fileName, imageReader.errorString()));
    }
}

void MainWindow::processImage(QImage &image)
{
    Q_ASSERT(chartView != nullptr);
    if (chartView == nullptr)
        return;

    auto chart = chartView->chart();
    Q_ASSERT(chart != nullptr);
    if (chart == nullptr)
        return;

    // calculate the histogram of R, G, B values.
    int reds[256] = {0};
    int greens[ARRAYSIZE(reds)] = {0};
    int blues[ARRAYSIZE(reds)] = {0};

#if 0
    // `pixel` says itself is expensive, and you poor guys just
    // can not afford it.
    auto imageWidth = image.width();
    auto imageHeight = image.height();

    for (auto h = 0; h < imageHeight; ++h)
    {
        for (auto w = 0; w < imageWidth; ++w)
        {
            auto rgb = image.pixel(w, h);
            ++reds[qRed(rgb)];
            ++greens[qGreen(rgb)];
            ++blues[qBlue(rgb)];
        }
    }
#elif 0
    auto format = image.format();
    if (format != QImage::Format_RGB32 && format != QImage::Format_ARGB32)
        image.convertToFormat(QImage::Format_ARGB32); // 0xAARRGGBB

    auto imageWidth = image.width();
    auto imageHeight = image.height();

    for (int y = 0; y < imageHeight; ++y)
    {
        auto scanLineRGBs = reinterpret_cast<const QRgb *>(image.scanLine(y));
        auto scanLineRGBsEnd = scanLineRGBs + imageWidth;
        for (auto px = scanLineRGBs; px < scanLineRGBsEnd; ++px)
        {
            ++reds[qRed(*px)];
            ++greens[qGreen(*px)];
            ++blues[qBlue(*px)];
        }
    }
#else
    auto format = image.format();
    if (format != QImage::Format_RGB32 && format != QImage::Format_ARGB32)
        image.convertToFormat(QImage::Format_ARGB32); // 0xAARRGGBB

    auto byteCount = image.byteCount();
    Q_ASSERT(byteCount % 4 == 0);
    auto pixelCount = byteCount / 4;

    auto pixelBegin = reinterpret_cast<const QRgb *>(image.constBits());
    auto pixelEnd = pixelBegin + pixelCount;
    for (auto px = pixelBegin; px < pixelEnd; ++px)
    {
        ++reds[qRed(*px)];
        ++greens[qGreen(*px)];
        ++blues[qBlue(*px)];
    }
#endif

    auto redLine = new QtCharts::QSplineSeries;
    redLine->setColor(Qt::GlobalColor::red);

    auto greenLine = new QtCharts::QSplineSeries;
    greenLine->setColor(Qt::GlobalColor::green);

    auto blueLine = new QtCharts::QSplineSeries();
    blueLine->setColor(Qt::GlobalColor::blue);

    for (auto i = 0; i < ARRAYSIZE(reds); ++i)
    {
        redLine->append(i, reds[i]);
        greenLine->append(i, greens[i]);
        blueLine->append(i, blues[i]);
    }

    chart->removeAllSeries();
    chart->addSeries(redLine);
    chart->addSeries(greenLine);
    chart->addSeries(blueLine);

    chart->createDefaultAxes();

    // X axis
    auto axisX = chart->axisX();
    axisX->setRange(-10, 260);
    axisX->setTitleText(tr("Color [0...255]"));

    // Y axis
    auto axisY = chart->axisY();
    axisY->setTitleText(tr("Distribution of pixels' color"));
}

void MainWindow::refreshPictureBox()
{
    if (pictureBox == nullptr || currentImage.isNull())
        return;

    auto pixmap = QPixmap::fromImage(currentImage).scaled(
        pictureBox->width(), pictureBox->height(), Qt::KeepAspectRatio);
    pictureBox->setPixmap(pixmap);
}
