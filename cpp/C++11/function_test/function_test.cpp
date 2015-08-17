// 2015-08-17T10:34+08:00
#include <cstdio>
#include <functional>

int foo() { return 0; }

struct Bar {
    int operator()() {
        return 1;
    }
    int hah() {
        return 101;
    }
};

int main()
{
    typedef int (*IFuncPtr)();
    IFuncPtr func0 = foo;
    //func0 = Bar(); // error!
    func0 = []() { return 42; };

    using IFunc = std::function<int ()>;

    IFunc func1 = foo;
    IFunc func2 = Bar();
    IFunc func3 = []() { return 42; };
    Bar bar;
    auto bound_hah = std::bind(&Bar::hah, std::placeholders::_1);
    IFunc func4 = std::bind(bound_hah, bar);

    std::printf("%d, %d, %d, %d, %d\n", func0(), func1(), func2(), func3(), func4());
    return 0;
}

// References:
// Effective C++ 3rd Edition/Item 35
