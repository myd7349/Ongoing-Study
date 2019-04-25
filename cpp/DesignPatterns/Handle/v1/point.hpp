#pragma once

class Point
{
public:
    Point(int x = 0, int y = 0)
        : x_(x), y_(y)
    {
    }

    int x() const { return x_; }
    int y() const { return y_; }

    Point &x(int xv)
    {
        x_ = xv;
        return *this;
    }

    Point &y(int yv)
    {
        y_ = yv;
        return *this;
    }

private:
    int x_;
    int y_;
};
