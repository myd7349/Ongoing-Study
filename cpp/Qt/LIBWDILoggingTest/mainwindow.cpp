#include "mainwindow.h"

#include <ctime>

#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include <QTimer>

#if defined(Q_OS_WIN32)
# define STRICT
# define WIN32_LEAN_AND_MEAN
# include <windows.h>

# define ENABLE_DEBUG_LOGGING
# include "libwdi.h"
# include "logging.h"

# define UM_WDI_LOG (WM_APP + 1)
#endif


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    listWidget = new QListWidget();
    setCentralWidget(listWidget);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(1000);

    if (wdi_register_logger(HWND(winId()), UM_WDI_LOG, 8192) != WDI_SUCCESS)
        QMessageBox::critical(nullptr, "Error:", "Failed to register logger!");
}

MainWindow::~MainWindow()
{
    wdi_unregister_logger(HWND(winId()));
}


bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = reinterpret_cast<MSG *>(message);

    switch (msg->message) {
    case UM_WDI_LOG:
    {
        char logBuffer[1024];
        DWORD size;

        wdi_read_logger(logBuffer, sizeof(logBuffer) / sizeof(logBuffer[0]), &size);
        listWidget->addItem(logBuffer);
    }
        break;
    default: break;
    }

    return QMainWindow::nativeEvent(eventType, message, result);
}


void MainWindow::tick()
{
    std::time_t ticks = std::time(nullptr);
    wdi_info(ctime(&ticks));
}


// References:
// https://stackoverflow.com/questions/26652783/qtnativeevent-calls
// https://stackoverflow.com/questions/11651852/how-to-use-qtimer
// https://stackoverflow.com/questions/18504995/clipboard-shortcut-hotkey-binding-with-qt-outside-of-application
