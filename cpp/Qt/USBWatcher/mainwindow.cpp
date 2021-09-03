#include "mainwindow.h"
#include "ui_mainwindow.h"

#if defined(Q_OS_WIN32)
#  define STRICT
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  include <dbt.h>

static HDEVNOTIFY hDeviceNotify = NULL;

static bool startUSBWatcher(QWidget *widget)
{
    Q_ASSERT(widget != NULL);
    if (NULL == widget) {
        return false;
    }

    if (hDeviceNotify != NULL) {
        return false;
    }

    HWND hWnd = (HWND)(widget->winId());

    GUID usbDevGuid = { 0x25dbce51, 0x6c8f, 0x4a72,
                          0x8a,0x6d,0xb5,0x4c,0x2b,0x4f,0xc8,0x35 };

    DEV_BROADCAST_DEVICEINTERFACE devNotifyFilter;
    ::SecureZeroMemory(&devNotifyFilter, sizeof(devNotifyFilter));
    devNotifyFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    devNotifyFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    devNotifyFilter.dbcc_classguid = usbDevGuid;

    hDeviceNotify = ::RegisterDeviceNotification(
                hWnd, &devNotifyFilter, DEVICE_NOTIFY_WINDOW_HANDLE);

    return hDeviceNotify != NULL;
}

static void stopUSBWatcher()
{
    if (hDeviceNotify != NULL) {
        if (::UnregisterDeviceNotification(hDeviceNotify)) {
            hDeviceNotify = NULL;
        } else {
            Q_ASSERT(false);
        }
    }
}

QChar firstDriverFromMask(ULONG uMask)
{
    char i;
    for (i = 0; i < 26; ++i) {
        if (uMask & 0x1) {
            break;
        }
        uMask >>= 1;
    }

    return QChar(i + 'A');
}

#else
#  error Unsupported platform currently
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
#if defined(Q_OS_WIN32)
    MSG *msg = reinterpret_cast<MSG *>(message);

    switch (msg->message) {
    case WM_CREATE: startUSBWatcher(this); break;
    case WM_DEVICECHANGE: {
        PDEV_BROADCAST_HDR pdbh = (PDEV_BROADCAST_HDR)(msg->lParam);

        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL: {
            if (DBT_DEVTYP_VOLUME == pdbh->dbch_devicetype) {
                PDEV_BROADCAST_VOLUME pdbv = (PDEV_BROADCAST_VOLUME)pdbh;
                /*if (pdbv->dbcv_flags & DBTF_MEDIA)*/ {
                    QChar vol = firstDriverFromMask(pdbv->dbcv_unitmask);
                    ui->listWidget->insertItem(ui->listWidget->count(), tr("Detecting the insertion of drive: ") + vol);
                }
            }
        }
            break;
        case DBT_DEVICEREMOVECOMPLETE: {
            if (DBT_DEVTYP_VOLUME == pdbh->dbch_devicetype) {
                PDEV_BROADCAST_VOLUME pdbv = (PDEV_BROADCAST_VOLUME)pdbh;
                /*if (pdbv->dbcv_flags & DBTF_MEDIA)*/ {
                    QChar vol = firstDriverFromMask(pdbv->dbcv_unitmask);
                    ui->listWidget->insertItem(ui->listWidget->count(), tr("Detecting the removal of drive: ") + vol);
                }
            }
        }
            break;
        default: break;
        }
    }
        break;
    case WM_DESTROY: stopUSBWatcher(); break;
    default: break;
    }
#endif
    return QMainWindow::nativeEvent(eventType, message, result);
}


// References:
// https://github.com/wang-bin/qdevicewatcher/blob/master/src/qdevicewatcher_win32.cpp
