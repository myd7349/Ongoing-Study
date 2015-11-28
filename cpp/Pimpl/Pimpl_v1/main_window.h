// 2015-11-19T12:46+08:00
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <memory>

class WidgetBase;

// Try to uncomment this line below and see what happens.
//#define DEFINE_MAINWINDOW_DESTRUCTOR (0)

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
    // 1. What if we use a std::shared_ptr here?
    // 2. Is MainWindow copyable?
    std::unique_ptr<WidgetBase> central_widget_;
};

#endif // MAIN_WINDOW_H_
