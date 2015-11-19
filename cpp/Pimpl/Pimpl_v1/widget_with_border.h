#ifndef WIDGET_WITH_BORDER_H_
#define WIDGET_WITH_BORDER_H_

#include "widget_base.h"

class WidgetWithBorder : public WidgetBase {
public:
    WidgetWithBorder(int width, int height, int border_size);

    int width() const;
    int height() const;

protected:
    int border_size_;
};

#endif // WIDGET_WITH_BORDER_H_
