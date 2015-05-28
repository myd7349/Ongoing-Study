#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setAutoFillBackground(true);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // 两张图片均为带透明色的png
    QPixmap pixmap1;
    pixmap1.load(":/img/1.png");
    QPixmap pixmap2;
    pixmap2.load(":/img/2.png");

    // 将两张图片“叠起来”
    QPixmap resultPixmap(pixmap1.width(), pixmap1.height());
    QPainter painter(&resultPixmap);
    painter.drawPixmap(0, 0, pixmap1);
    painter.drawPixmap(0, 0, pixmap2);

    imageLabel->setPixmap(resultPixmap);

    convButton = new QPushButton(tr("&Convert"));
    connect(convButton, SIGNAL(clicked()), this, SLOT(convert()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(convButton);

    setLayout(mainLayout);
}

Dialog::~Dialog()
{
}

void Dialog::convert()
{
    imageLabel->clear();

    QImage image1;
    image1.load(":/img/1.png");
    QImage image2;
    image2.load(":/img/2.png");

#if 0
    // 将图片中黑色数字变为红色
    // 由于在用PS作图时，数字有进行反走样处理，所以
    // 替换的并不彻底。
    int width = image2.width();
    int height = image2.height();
    for (int w = 0; w < width; ++w) {
        for (int h = 0; h < height; ++h) {
            if (image2.pixel(w, h) == qRgba(0, 0, 0, 255)) {
                image2.setPixel(w, h, qRgba(255, 0, 0, 255));
            }
        }
    }
#else
    // 将非透明部分加上所需颜色值。
    // 这种情况下，即使非透明部分经过了反走样处理，
    // 得到的效果也会比较理想。
    int width = image2.width();
    int height = image2.height();
    for (int w = 0; w < width; ++w) {
        for (int h = 0; h < height; ++h) {
            QRgb rgb = image2.pixel(w, h);
            if (qAlpha(rgb) != 0) {
                image2.setPixel(w, h, rgb + qRgba(255, 0, 0, 0));
            }
        }
    }
#endif

    // 实际上，QImage、QPixmap提供的图像处理函数比较少，
    // QTransform也主要用来实现图像的几何变换。
    // 如果真的对图像处理要求比较高的话。
    // 确实应该考虑OpenCV。
    //  比如，OpenCV可以直接将一个颜色值加到一张图像的
    // 每个像素值上。

    QPixmap resultPixmap(image1.width(), image1.height());
    QPainter painter(&resultPixmap);
    painter.drawImage(0, 0, image1);
    painter.drawImage(0, 0, image2);

    imageLabel->setPixmap(resultPixmap);
}
