#pragma once

#include "ConfigItem.hpp"


struct Point
{
    Point(float xv = .0f, float yv = .0f) // 0f won't work.
        : x(xv), y(yv)
    {
    }

    float x, y;
};


inline bool operator==(const Point &lhs, const Point &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}


inline bool operator!=(const Point &lhs, const Point &rhs)
{
    return !operator==(lhs, rhs);
}


typedef ConfigItem<Point> PointItem;
