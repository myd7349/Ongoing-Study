#include "widget_with_border.h"

WidgetWithBorder::WidgetWithBorder(int width, int height, int border_size)
    : WidgetBase(width, height), border_size_(border_size)
{
}

int WidgetWithBorder::width() const
{
    return width_ - 2 * border_size_;
}


int WidgetWithBorder::height() const
{
    return height_ - 2 * border_size_;
}
