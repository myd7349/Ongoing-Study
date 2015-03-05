// 2015-03-05T08:46+08:00
#include <cassert>
#include <iostream>
#include <typeinfo>

void test_0()
{
#if 0
    int i = 42;

    // error: cannot dynamic_cast '& i' (of type 'int*') to type 'double*'
    // (target is not pointer or reference to class)|
    double d = *dynamic_cast<double *>(&i);
#endif
}

void test_1()
{
#if 0
    int i = 42;

    // error: cannot dynamic_cast '& i' (of type 'int*') to type 'void*'
    // (source is not a pointer to class)
    void *v = dynamic_cast<void *>(&i);
#endif
}

void test_2()
{
#if 0
    // error: cannot dynamic_cast '& foo' (of type 'class main()::Foo*') to type 'class main()::Bar*'
    // (source type is not polymorphic)|
    class Foo {};
    class Bar {};

    Foo foo;
    Bar *bar = dynamic_cast<Bar *>(&foo);
#endif
}

void test_3()
{
    class Hello {
        virtual void hi() {}
    };
    class World {
    };
    Hello hello;
    World *world = dynamic_cast<World *>(&hello);
    assert(nullptr == world);
    try {
        dynamic_cast<World &>(hello);
    } catch (const std::bad_cast &e) {
        std::cerr << e.what() << std::endl;
    }
}

int main()
{
    test_0();
    test_1();
    test_2();
    test_3();

    return 0;
}
// References:
// [dynamic_cast conversion](http://en.cppreference.com/w/cpp/language/dynamic_cast)
