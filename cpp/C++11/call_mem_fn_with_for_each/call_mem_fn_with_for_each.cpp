// 2015-12-25T11:20+08:00
// Merry Christmas!
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>

class Shape {
public:
    Shape() : id_(count_++) {}

    virtual void draw(std::ostream &os) = 0;
    void print_id() {
        std::cout << "Shape #" << id_ << std::endl;
    }

private:
    int id_;

    static int count_;
};

int Shape::count_ = 0;

class Circle : public Shape {
public:
    Circle(int radius) : radius_(radius) {}

    void draw(std::ostream &os) {
        os << "Circle! Radius: " << radius_ << std::endl;
    }

private:
    int radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(int l, int t, int r, int b)
      : left_(l), top_(t), right_(r), bottom_(b) {
    }

    void draw(std::ostream &os) {
        os << "Rectangle! "
           << "Left:"   << left_   << ", "
           << "Top:"    << top_    << ", "
           << "Right:"  << right_  << ", "
           << "Bottom:" << bottom_ << std::endl;
    }

private:
    int left_;
    int top_;
    int right_;
    int bottom_;
};

int main()
{
    Shape *shapes[] = {
        new Circle(3),
        new Rectangle(0, 0, 1, 1),
        new Rectangle(1, 2, 3, 4),
    };

    std::for_each(std::begin(shapes), std::end(shapes),
        std::mem_fun(&Shape::print_id));

    std::for_each(std::begin(shapes), std::end(shapes),
        std::bind(&Shape::draw, std::placeholders::_1, std::ref(std::cout)));

    std::for_each(std::begin(shapes), std::end(shapes),
        std::default_delete<Shape>());

    using ShapePtr = std::shared_ptr<Shape>;
    ShapePtr safe_shapes[] = {
        std::make_shared<Circle>(1),
        std::make_shared<Circle>(2),
        std::make_shared<Circle>(3),
        std::make_shared<Rectangle>(0, 0, 100, 100),
        std::make_shared<Rectangle>(0, 0, 640, 480),
    };

    // nested bind
    std::for_each(std::begin(safe_shapes), std::end(safe_shapes),
        std::bind(&Shape::draw,
                  std::bind(&ShapePtr::operator->, std::placeholders::_1),
                  std::ref(std::cout)
            )
        );

    return 0;
}

// References:
// 1. std::for_each, calling member function with reference parameter:
//    http://stackoverflow.com/questions/637441/stdfor-each-calling-member-function-with-reference-parameter
// 2. Can I call `delete` on a vector of pointers in C++ via for_each <algorithm>?
//    http://stackoverflow.com/questions/3505343/can-i-call-delete-on-a-vector-of-pointers-in-c-via-for-each-algorithm
// 3. Call member function on object vector
//    http://stackoverflow.com/questions/12668598/call-member-function-on-object-vector
// 4. Using nested boost::binds
//    http://stackoverflow.com/questions/12015256/using-nested-boostbinds
