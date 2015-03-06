// 2015-03-06T08:35+08:00
#include <iomanip>
#include <iostream>
#include <typeinfo>

#include "../../common.h"

class Base {
public:
    virtual void foo() {}
};

class Derived : public Base {
public:
    void foo() {}
};

#define TEST_CASE(expr) \
    std::cout << std::boolalpha << STR(expr) << ": " << (expr) << std::endl

int main()
{
    Derived d;
    Base *pb = &d;

    TEST_CASE(typeid(pb) == typeid(Base *));
    TEST_CASE(typeid(pb) == typeid(Derived *));
    TEST_CASE(typeid(*pb) == typeid(Base));
    TEST_CASE(typeid(*pb) == typeid(Derived));

    return 0;
}
