#pragma once

#ifndef NDEBUG
#include <iostream>
#endif


class Point
{
public:
    Point(int x = 0, int y = 0)
        : x_(x), y_(y)
    {
#ifndef NDEBUG
        std::cout << __func__ << '(' << x_ << ", " << y_ << ")\n";
#endif
    }

#ifndef NDEBUG
    Point(const Point &pt)
        : x_(pt.x_), y_(pt.y_)
    {
        std::cout << __func__ << '(' << x_ << ", " << y_ << ")\n";
    }

    ~Point()
    {
        std::cout << __func__ << '(' << x_ << ", " << y_ << ")\n";
    }
#endif

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
