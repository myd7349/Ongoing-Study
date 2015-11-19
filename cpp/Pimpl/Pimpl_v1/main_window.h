// 2015-11-19T12:46+08:00
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <memory>

class WidgetBase;

#ifndef DEFINE_MAINWINDOW_DESTRUCTOR
# define DEFINE_MAINWINDOW_DESTRUCTOR (1)
#endif

class MainWindow {
public:
    MainWindow(int width, int height, bool has_border);

#if DEFINE_MAINWINDOW_DESTRUCTOR
    ~MainWindow();
#endif

    void print_size();

private:
    std::unique_ptr<WidgetBase> central_widget_;
};

#endif // MAIN_WINDOW_H_
