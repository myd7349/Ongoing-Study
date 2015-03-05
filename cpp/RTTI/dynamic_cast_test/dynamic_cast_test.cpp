// 2015-03-05T08:46+08:00
#include <cassert>
#include <iostream>
#include <typeinfo>

// To do a dynamic_cast:
//   1. The source type must be pointer or reference to class. And this class
//      is polymorphic.
//   2. The target type must be pointer or reference to class, or a pointer of
//      type void (that is, "void *").
void test_0()
{
#if 0
    int i = 42;

    // error: cannot dynamic_cast '& i' (of type 'int*') to type 'double*'
    // (target is not pointer or reference to class)|
    double *d = dynamic_cast<double *>(&i);
#endif
}

void test_1()
{
#if 0
    // error: cannot dynamic_cast 'nullptr' (of type 'std::nullptr_t') to type 'void*'
    // (source is not a pointer)|
    dynamic_cast<void *>(nullptr);
    dynamic_cast<void *>(NULL);
#endif

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
    // (dynamic_cast<World *>(&hello)source type is not polymorphic)|
    class Foo {};
    class Bar {};

    Foo foo;
    Bar *bar = dynamic_cast<Bar *>(&foo);
#endif
}

// Downcasting test
void test_3()
{
    class Hello {
        virtual void hi() {}
    };
    class World {
    };

    Hello hello;
    assert(nullptr == dynamic_cast<World *>(&hello));

    void *pv = dynamic_cast<void *>(&hello);
    assert(pv != nullptr);

#if 0
    // Oops! Remember test_1?
    assert(dynamic_cast<Hello *>(pv) != nullptr);
    assert(nullptr == dynamic_cast<World *>(pv));
#endif

    try {
        dynamic_cast<World &>(hello);
    } catch (const std::bad_cast &e) {
        std::cerr << e.what() << std::endl;
    }
}

// TODO: Side cast
void test_4()
{
}

int main()
{
    test_0();
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}
// References:
// [dynamic_cast](http://en.wikipedia.org/wiki/Dynamic_cast)
// [dynamic_cast conversion](http://en.cppreference.com/w/cpp/language/dynamic_cast)
// [cv (const and volatile) type qualifiers](http://en.cppreference.com/w/cpp/language/cv)
// [Downcasting](http://en.wikipedia.org/wiki/Downcasting)
