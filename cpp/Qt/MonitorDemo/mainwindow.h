#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>


#if defined(Q_OS_WIN32)
# define STRICT
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# error Unsupported platform currently
#endif


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void log(const QString &msg);

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    void onCreate();
    void onDestroy();
    void onDeviceChange(WPARAM wParam, LPARAM lParam);
    void onDevModeChange(WPARAM wParam, LPARAM lParam);
    void onDisplayChange(WPARAM wParam, LPARAM lParam);
    void onSettingChange(WPARAM wParam, LPARAM lParam);

    QListWidget *listWidget = nullptr;
    HDEVNOTIFY deviceNotifyHandle_ = nullptr;
};

#endif // MAINWINDOW_H
