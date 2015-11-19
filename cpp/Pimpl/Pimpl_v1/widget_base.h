// 2015-11-19T11:53+08:00
#ifndef WIDGET_BASE_H_
#define WIDGET_BASE_H_

class WidgetBase {
public:
    WidgetBase(int width, int height) {
        width_ = width;
        height_ = height;
    }

    virtual ~WidgetBase() = default;

    virtual int width() const = 0;
    virtual int height() const = 0;

protected:
    int width_ = 640;
    int height_ = 480;
};

#endif // WIDGET_BASE_H_
