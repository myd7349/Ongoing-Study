// 2014-12-02T16:30+08:00
// In C++, we can use typeid operator to get the RTTI of an expression or a type.
// However, different C++ compilers provide different type names when we wrote:
//     std::cout << typeid(type/expression).name();
// The names returned by g++ is extremely unreadable, so I just STFG and wrote this sample.

#include <initializer_list>
#include <iostream>
#include <typeinfo>

#include "uniform_typename.h"

int main()
{
    std::cout << TYPE_NAME(int) << std::endl; // int
    std::cout << TYPE_NAME(1 < 2) << std::endl; // bool

#if defined(_MSC_VER)
	auto lst = new std::initializer_list<int>({1, 2, 3, 4});
#else
	// In VS2013, code below causes a compile-time error.
	auto lst = new auto({1, 2, 3, 4}); // C++11 is needed.
#endif
    std::cout << TYPE_NAME(lst) << std::endl; // std::initializer_list<int>*
    delete lst;

    return 0;
}
