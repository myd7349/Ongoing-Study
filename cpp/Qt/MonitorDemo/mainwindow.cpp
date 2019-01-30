#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include <dbt.h>


// https://github.com/Enlightenment/efl/blob/32cebe903d39ef212b19f040e68cd35bcfe2b21b/src/lib/ecore_win32/ecore_win32_monitor.c
#ifndef GUID_DEVINTERFACE_MONITOR
static GUID GUID_DEVINTERFACE_MONITOR = {0xe6f07b5f, 0xee97, 0x4a90, { 0xb0, 0x76, 0x33, 0xf5, 0x7b, 0xf4, 0xea, 0xa7} };
#endif

#define IN_CASE(c) case c: msg += #c


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    listWidget = new QListWidget();
    setCentralWidget(listWidget);

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            QSize(800, 640),
            qApp->desktop()->availableGeometry()
        )
    );
}


MainWindow::~MainWindow()
{
}


void MainWindow::log(const QString &msg)
{
    listWidget->addItem(msg);
    listWidget->scrollToBottom();
}


void MainWindow::onCreate()
{
    HWND handle = reinterpret_cast<HWND>(winId());

    DEV_BROADCAST_DEVICEINTERFACE devNotifyFilter {};
    devNotifyFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    devNotifyFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    devNotifyFilter.dbcc_classguid = GUID_DEVINTERFACE_MONITOR;

    deviceNotifyHandle_ = RegisterDeviceNotification(
        handle, &devNotifyFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
    Q_ASSERT(deviceNotifyHandle_ != nullptr);
}


void MainWindow::onDestroy()
{
    if (deviceNotifyHandle_ != nullptr)
    {
        if (UnregisterDeviceNotification(deviceNotifyHandle_))
            deviceNotifyHandle_ = nullptr;
        else
            Q_ASSERT(false);
    }
}


void MainWindow::onDeviceChange(WPARAM wParam, LPARAM lParam)
{
    QString msg("WM_DEVICECHANGE: ");

    PDEV_BROADCAST_HDR pdbh = reinterpret_cast<PDEV_BROADCAST_HDR>(lParam);
    if (pdbh == nullptr)
    {
        switch (wParam)
        {
        IN_CASE(DBT_DEVICEARRIVAL); break;
        IN_CASE(DBT_DEVICEREMOVECOMPLETE); break;
        IN_CASE(DBT_DEVNODES_CHANGED);
        {
            msg += tr(": Monitors: %1")
                .arg(GetSystemMetrics(SM_CMONITORS));
        }
            break;
        default: msg += tr("wParam: %1, lParam: %2").arg(wParam, lParam); break;
        }
    }

    log(msg);
}


void MainWindow::onDisplayChange(WPARAM wParam, LPARAM lParam)
{
    WORD width = LOWORD(lParam);
    WORD height = HIWORD(lParam);

    QString msg = tr("WM_DISPLAYCHANGE: %1bpp, %2x%3")
        .arg(wParam).arg(width).arg(height);
    log(msg);
}


void MainWindow::onSettingChange(WPARAM wParam, LPARAM lParam)
{
    QString msg("WM_SETTINGCHANGE: ");

    switch (wParam)
    {
    IN_CASE(SPI_ICONVERTICALSPACING); break;
    IN_CASE(SPI_SETDESKWALLPAPER); break;
    IN_CASE(SPI_SETWORKAREA); break;
    IN_CASE(SPI_SETLOGICALDPIOVERRIDE); break;
    default: msg += tr("wParam: %1, lParam: %2").arg(wParam, lParam); break;
    }

    log(msg);
}


bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = static_cast<MSG *>(message);

    switch (msg->message)
    {
    case WM_CREATE: onCreate(); break;
    case WM_DEVICECHANGE: onDeviceChange(msg->wParam, msg->lParam); break;
    case WM_DISPLAYCHANGE: onDisplayChange(msg->wParam, msg->lParam); break;
    case WM_SETTINGCHANGE: onSettingChange(msg->wParam, msg->lParam); break;
    case WM_DESTROY: onDestroy(); break;
    default: break;
    }

    return QMainWindow::nativeEvent(eventType, message, result);
}


// References:
// https://stackoverflow.com/questions/33762140/what-is-the-notification-when-the-number-of-monitors-changes
// https://stackoverflow.com/questions/310451/should-i-use-static-cast-or-reinterpret-cast-when-casting-a-void-to-whatever
// https://stackoverflow.com/questions/5013596/when-convert-a-void-pointer-to-a-specific-type-pointer-which-casting-symbol-is
// https://www.codeproject.com/articles/119168/hardware-change-detection
// https://docs.microsoft.com/en-us/windows-hardware/drivers/install/guid-devinterface-monitor
// https://stackoverflow.com/questions/35943798/getting-notified-when-monitor-turns-on-off-using-registerdevicenotification
// https://pastebin.com/bSSWjwir
// https://stackoverflow.com/questions/706352/use-registerdevicenotification-for-all-usb-devices
// https://social.msdn.microsoft.com/Forums/vstudio/en-US/1efacfa6-3c8d-4d49-aa3c-752f819c451f/detecting-the-connectiondisconnection-of-a-monitor-in-vista-and-windows-7
