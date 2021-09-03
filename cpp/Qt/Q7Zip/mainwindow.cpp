#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDir>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QStylePainter>

#include "Q7Zip.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    q7zip_ = Q7Zip::getInstance();

    ui->setupUi(this);

    setWindowTitle(tr("Q7Zip"));

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            QSize(800, 640),
            qApp->primaryScreen()->availableGeometry()
        )
    );

    connect(ui->extractArchivePushButton, SIGNAL(clicked()), this, SLOT(extractArchive()));
    connect(ui->createArchivePushButton, SIGNAL(clicked()), this, SLOT(createArchive()));

    ui->statusBar->showMessage(tr("LZMA SDK version: ") + q7zip_->lzma_sdk_version());

    progressDialog_ = new QProgressDialog(this);
    progressDialog_->setWindowModality(Qt::WindowModal);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::extractArchive()
{
    auto archiveFilePath = QFileDialog::getOpenFileName(
        this,
        tr("Select archive:"),
        QDir::currentPath(),
        tr("Archive Files (*.7z *.zip);;All Files (*.*)"));
    if (!archiveFilePath.isEmpty())
    {
        progressDialog_->setWindowTitle(tr("Extracting archive..."));
        progressDialog_->setRange(0, 100);
        progressDialog_->setValue(0);

        connect(q7zip_, SIGNAL(extracting_filename_signal(const QString)),
            progressDialog_, SLOT(setLabelText(const QString &)));
        connect(q7zip_, SIGNAL(extract_percentage_signal(int)),
            progressDialog_, SLOT(setValue(int)));

        q7zip_->extract(archiveFilePath, "D:\\test");
    }
}


void MainWindow::createArchive()
{

}


// References:
// [Qt 5 : update QProgressBar during QThread work via signal](https://stackoverflow.com/questions/35673201/qt-5-update-qprogressbar-during-qthread-work-via-signal/35673612)
