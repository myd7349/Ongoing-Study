#include "main_window.h"
#include "widget_no_border.h"
#include "widget_with_border.h"

#include <iostream>

MainWindow::MainWindow(int width, int height, bool has_border)
{
    if (has_border) {
        central_widget_.reset(new WidgetWithBorder(width, height, 5));
    } else {
        central_widget_.reset(new WidgetNoBorder(width, height));
    }
}

#if DEFINE_MAINWINDOW_DESTRUCTOR
MainWindow::~MainWindow()
{
}
#endif


void MainWindow::print_size()
{
    std::cout << "Width: " << central_widget_->width()
              << ", Height: " << central_widget_->height()
              << std::endl;
}
