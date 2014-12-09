// 2014-11-13T21:56+08:00
// bind1st, bind2nd and several other function binders in <functional> are deprecated since C++11.
// However, C++11 provides us with a more powerful, generalised binder: std::bind.
// Those URLs below may give you the answer why do we prefer std::bind to those old binds:
// * [Deprecated binders and adaptors](http://thenewcpp.wordpress.com/2012/04/25/deprecated-binders-and-adaptors/)
// * [Why might std::bind1st be considered ¡°almost unusable¡±?](http://stackoverflow.com/questions/6609337/why-might-stdbind1st-be-considered-almost-unusable)

#include <cassert>
#include <functional>
#include <iostream>
#include <type_traits>

// 2014-12-09T17:17+08:00
// 0. std::bind and overloaded function
// When I was doing a test on MongoDB's C++ driver, I encountered this problem:
// Ongoing-study/cpp/GridFS_test
// The answer is here:
// * [std::bind and overloaded function](http://stackoverflow.com/questions/13064698/stdbind-and-overloaded-function)
// That is: I should do a cast explicitly.
// TODO: standard
namespace bind_and_overloaded_function
{
    void say_hello()
    {
        std::cout << "Hello, world!\n";
    }

    void say_hello(const char *msg)
    {
        std::cout << msg << std::endl;
    }

    void say_hello(const char *msg, int repeat)
    {
        for (int i = 0; i < repeat; ++i) {
            std::cout << "#" << i << " " << msg << std::endl;
        }
    }

    void test()
    {
        auto simple_is_beautiful = std::bind(
            static_cast<void (*)(const char *)>(say_hello), "Simple is Beautiful!");
        assert(std::is_bind_expression<decltype(simple_is_beautiful)>::value);
        simple_is_beautiful();
    }
}

// 1.

int main()
{
    bind_and_overloaded_function::test();

    return 0;
}
