#ifndef WIDGET_NO_BORDER_H_
#define WIDGET_NO_BORDER_H_

#include "widget_base.h"

class WidgetNoBorder : public WidgetBase {
public:
    WidgetNoBorder(int width, int height)
        : WidgetBase(width, height) {
    }

    int width() const { return width_; }
    int height() const { return height_; }
};

#endif // WIDGET_NO_BORDER_H_
