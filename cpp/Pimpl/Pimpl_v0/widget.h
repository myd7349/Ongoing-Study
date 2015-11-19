// 2015-11-19T11:53+08:00
#ifndef WIDGET_H_
#define WIDGET_H_

#include <memory>

class Widget {
public:
    Widget();

    void print_size();

private:
    class WidgetImpl;
    std::shared_ptr<WidgetImpl> widget_;
};

#endif // WIDGET_H_
