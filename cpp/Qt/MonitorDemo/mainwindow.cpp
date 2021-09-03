#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

#include <dbt.h>

#include "MultiMonitor.h"


// https://github.com/Enlightenment/efl/blob/32cebe903d39ef212b19f040e68cd35bcfe2b21b/src/lib/ecore_win32/ecore_win32_monitor.c
#ifndef GUID_DEVINTERFACE_MONITOR
static GUID GUID_DEVINTERFACE_MONITOR = {0xe6f07b5f, 0xee97, 0x4a90, { 0xb0, 0x76, 0x33, 0xf5, 0x7b, 0xf4, 0xea, 0xa7} };
#endif

#define IN_CASE(c) case c: msg += #c


QString GetMonitorInformation()
{
    std::vector<MONITORINFOEX> monitorInfoVector;
    GetAllMonitorInfos(monitorInfoVector);

    std::map<std::wstring, DisplayDeviceInfo> devicesMap;
    GetAllDisplayDevices(devicesMap);

    QString info = QString(
        "\n"
        "        Monitors: %1\n"
        "        CXSCREEN: %2           CYSCREEN: %3\n"
        "        CXVIRTUALSCREEN: %4    CYVIRTUALSCREEN: %5\n"
        "        XVIRTUALSCREEN: %6     YVIRTUALSCREEN: %7\n"
        "--------------------------------------------------------------------------------\n"
        )
        .arg(GetSystemMetrics(SM_CMONITORS))
        .arg(GetSystemMetrics(SM_CXSCREEN))
        .arg(GetSystemMetrics(SM_CYSCREEN))
        .arg(GetSystemMetrics(SM_CXVIRTUALSCREEN))
        .arg(GetSystemMetrics(SM_CYVIRTUALSCREEN))
        .arg(GetSystemMetrics(SM_XVIRTUALSCREEN))
        .arg(GetSystemMetrics(SM_YVIRTUALSCREEN))
        ;

    for (const auto &mi : monitorInfoVector)
    {
        info += QString(
            "        HMONITOR: %1\n"
            "        rcMonitor: (%2, %3, %4, %5) Width: %6, Height: %7\n"
            "        rcWork: (%8, %9, %10, %11) Width: %12, Height: %13\n"
            "        Is primary? %14\n"
            "        Device number: %15\n"
            "        Device name: %16\n"
            "        Device string: %17\n"
            "        Device ID: %18\n"
            "        Device key: %19\n"
            "--------------------------------------------------------------------------------\n")
            .arg(reinterpret_cast<quintptr>(MonitorFromRect(&mi.rcWork, MONITOR_DEFAULTTONULL)))
            .arg(mi.rcMonitor.left)
            .arg(mi.rcMonitor.top)
            .arg(mi.rcMonitor.right)
            .arg(mi.rcMonitor.bottom)
            .arg(mi.rcMonitor.right - mi.rcMonitor.left)
            .arg(mi.rcMonitor.bottom - mi.rcMonitor.top)
            .arg(mi.rcWork.left)
            .arg(mi.rcWork.top)
            .arg(mi.rcWork.right)
            .arg(mi.rcWork.bottom)
            .arg(mi.rcWork.right - mi.rcWork.left)
            .arg(mi.rcWork.bottom - mi.rcWork.top)
            .arg(mi.dwFlags == MONITORINFOF_PRIMARY)
            .arg(devicesMap[mi.szDevice].dwDevNum)
            .arg(QString::fromWCharArray(mi.szDevice))
            .arg(QString::fromWCharArray(devicesMap[mi.szDevice].DeviceString))
            .arg(QString::fromWCharArray(devicesMap[mi.szDevice].DeviceID))
            .arg(QString::fromWCharArray(devicesMap[mi.szDevice].DeviceKey))
            ;
    }

    return info;
}


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
            qApp->primaryScreen()->availableGeometry()
        )
    );

    log(GetMonitorInformation());
}


MainWindow::~MainWindow()
{
}


void MainWindow::log(const QString &msg)
{
    QStringList lines = msg.split('\n', Qt::SkipEmptyParts);

    for (QStringList::size_type i = 0; i < lines.size(); ++i)
    {
        QString line = (i == 0 ? "" : "        ") + lines[i];
        listWidget->addItem(lines[i]);
    }

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
            msg += GetMonitorInformation();
            break;
        default: msg += tr("wParam: %1, lParam: %2").arg(wParam, lParam); break;
        }
    }

    log(msg);
}


void MainWindow::onDevModeChange(WPARAM wParam, LPARAM lParam)
{
    log(tr("WM_DEVMODECHANGE: wParam: %1, lParam: %2").arg(wParam, lParam));
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
    IN_CASE(SPI_SETWORKAREA);
        msg += GetMonitorInformation();
        break;
    IN_CASE(SPI_SETLOGICALDPIOVERRIDE); break;
    default: msg += tr("wParam: %1, lParam: %2").arg(wParam, lParam); break;
    }

    log(msg);
}


bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG *msg = static_cast<MSG *>(message);

    switch (msg->message)
    {
    case WM_CREATE: onCreate(); break;
    case WM_DEVICECHANGE: onDeviceChange(msg->wParam, msg->lParam); break;
    case WM_DEVMODECHANGE: onDevModeChange(msg->wParam, msg->lParam); break;
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
// https://stackoverflow.com/questions/26312505/multiple-monitors-and-handles
// https://stackoverflow.com/questions/8881923/how-to-convert-a-pointer-value-to-qstring
// https://www.codeproject.com/articles/2522/multiple-monitor-support
// https://stackoverflow.com/questions/8040627/convert-wchar-to-qstring-in-qt
// https://github.com/wang-bin/qdevicewatcher/blob/master/src/qdevicewatcher_win32.cpp
