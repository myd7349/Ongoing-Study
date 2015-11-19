#include "widget.h"

#include <iostream>

class Widget::WidgetImpl {
public:
    WidgetImpl(int width, int height) {
        width_ = width;
        height_ = height;
    }

    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_ = 640;
    int height_ = 480;
};


Widget::Widget()
    : widget_(new WidgetImpl(1280, 1050))
{
}


void Widget::print_size()
{
    std::cout << "Width: " << widget_->width()
              << ", Height: " << widget_->height() << std::endl;
}
