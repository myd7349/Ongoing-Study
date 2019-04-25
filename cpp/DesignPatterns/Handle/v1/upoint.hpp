#pragma once

#include "point.hpp"


class UPoint
{
    friend class Handle;
    friend class HandlePtr;
    friend class HandleValue;

    Point pt_;
    int use_count_;

    UPoint()
        : use_count_(1)
    {
    }

    UPoint(int x, int y)
        : pt_(x, y), use_count_(1)
    {
    }

    UPoint(const Point &pt)
        : pt_(pt), use_count_(1)
    {
    }
};
