// 2017-06-24T15:54+08:00
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>


class Point
{
public:
    Point(double x, double y)
        : x(x), y(y)
    {
    }

#if 0
    // error:
    Point(double r, double theta)
        : x(r * std::cos(theta)), y(r * std::sin(theta))
    {
    }
#endif

    static Point Cartesian(double x, double y)
    {
        return Point(x, y);
    }

    static Point Polar(double r, double theta)
    {
        return Point(r * std::cos(theta), r * std::sin(theta));
    }

    double x;
    double y;

    std::string ToString() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

int main()
{
    Point p1(1, 2);
    Point p2 = Point::Polar(2, 60.0 / 180.0 * M_PI);

    std::cout << p1.ToString() << std::endl;
    std::cout << p2.ToString() << std::endl;

    return 0;
}

// References:
// [More C++ Idioms/Named Constructor](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Constructor)
// 《冒号课堂》第13课 设计模式
