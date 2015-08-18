// 2014-11-13T21:56+08:00
// bind1st, bind2nd and several other function binders in <functional> are deprecated since C++11.
// However, C++11 provides us with a more powerful, generalised binder: std::bind.
// Those URLs below may give you the answer why do we prefer std::bind to those old binds:
// * [Deprecated binders and adaptors](http://thenewcpp.wordpress.com/2012/04/25/deprecated-binders-and-adaptors/)
// * [Why might std::bind1st be considered ¡°almost unusable¡±?](http://stackoverflow.com/questions/6609337/why-might-stdbind1st-be-considered-almost-unusable)

// 2015-08-18T17:33+08:00
// Effective C++ 3rd Edition/Item 54:
// tr1::bind, which does everything the STL binders bind1st and bind2nd do, plus
// much more. Unlike the pre-TR1 binders, tr1::bind works with both const and
// non-const member functions. Unlike the pre-TR1 binders, TR1::bind works with
// by-reference parameters. Unlike the pre-TR1 binders, TR1::bind handles function
// pointers without help, so there's no need to mess with ptr_fun, mem_fun, or
// mem_fun_ref before calling TR1::bind. Simply put, TR1::bind is a second-generation
// binding facility that is significantly better than its predecessor.

#include <cassert>
#include <functional>
#include <iostream>
#include <type_traits>

#include <boost/core/noncopyable.hpp>

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
    void say_what()
    {
        std::cout << "Hello, world!\n";
    }

    void say_what(const char *msg)
    {
        std::cout << msg << std::endl;
    }

    void say_what(const char *msg, int repeat)
    {
        for (int i = 0; i < repeat; ++i) {
            std::cout << "#" << i << " " << msg << std::endl;
        }
    }

    void test()
    {
        auto simple_is_beautiful = std::bind(
            static_cast<void (*)(const char *)>(say_what), "Simple is Beautiful!");
        assert(std::is_bind_expression<decltype(simple_is_beautiful)>::value);
        simple_is_beautiful();
    }
}

// 2014-12-10T09:33+08:00
// 1. bind with non-copyable parameters
namespace bind_with_noncopyable_parameters
{
    class Individual : public boost::noncopyable {
    public:
        virtual void say() const = 0;
    };
    class DonaldKnuth : public Individual {
    public:
        virtual void say() const override {
            std::cout << "Premature optimization is the root of all evil\n";
        }
    };

    void who_say(const Individual &individual)
    {
        individual.say();
    }

    void test()
    {
        DonaldKnuth guru;
        std::bind(who_say, std::ref(guru))();
    }
}

int main()
{
    bind_and_overloaded_function::test();

    bind_with_noncopyable_parameters::test();

    return 0;
}
