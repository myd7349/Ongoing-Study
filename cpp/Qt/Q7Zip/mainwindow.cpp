#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDir>
#include <QtCore/QThread>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QStylePainter>

#include "ExtractionWorker.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    q7zip_ = new Q7Zip(this);

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
        QThread* thread = new QThread(this);

        ExtractionWorker *extractionWorker = new ExtractionWorker;
        extractionWorker->moveToThread(thread);

        connect(thread, SIGNAL(started()), extractionWorker, SLOT(extract()));

        thread->start();

        auto progressDialog = new QProgressDialog(this);
        progressDialog->setWindowModality(Qt::WindowModal);
        progressDialog->setWindowTitle(tr("Extracting archive..."));
        progressDialog->setRange(0, 100);
        progressDialog->setValue(0);

        connect(q7zip_, SIGNAL(extracting_filename_signal(const QString)),
            progressDialog, SLOT(setLabelText(const QString &)));
        connect(q7zip_, SIGNAL(extract_percentage_signal(int)),
            progressDialog, SLOT(setValue(int)));

        q7zip_->extract(archiveFilePath, "F:\\test");
    }
}


void MainWindow::createArchive()
{

}


// References:
// [Qt 5 : update QProgressBar during QThread work via signal](https://stackoverflow.com/questions/35673201/qt-5-update-qprogressbar-during-qthread-work-via-signal/35673612)
// [How can I set text of label when a function is running?](https://stackoverflow.com/questions/22715564/how-can-i-set-text-of-label-when-a-function-is-running)
// [what is the correct way to implement a QThread](https://stackoverflow.com/questions/4093159/what-is-the-correct-way-to-implement-a-qthread-example-please)
// [How To Really, Truly Use QThreads; The Full Explanation](https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/)
// [Threading without the headache](https://www.qt.io/blog/2006/12/04/threading-without-the-headache)
// [Is Qt's QBuffer thread safe?](https://stackoverflow.com/questions/13865232/is-qts-qbuffer-thread-safe)
// [Qt signal argument thread safety](https://stackoverflow.com/questions/31118507/qt-signal-argument-thread-safety)
