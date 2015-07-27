// 2014-12-02T16:30+08:00
// In C++, we can use typeid operator to get the RTTI of an expression or a type.
// However, different C++ compilers provide different type names when we wrote:
//     std::cout << typeid(type/expression).name();
// The names returned by g++ are extremely unreadable, so I just STFG and wrote this sample.

#include <initializer_list>
#include <iostream>
#include <typeinfo>

#include "../common.h"
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

    std::cout << TYPE_NAME(std::cout) << std::endl;
    std::cout << TYPE_NAME(std::cerr) << std::endl;
    std::cout << TYPE_NAME(std::clog) << std::endl;
    //std::cout << TYPE_NAME(std::endl) << std::endl;

    // According to cppreference.com:
    // (1)  If type is a reference type, the result refers to the referenced type.
    std::cout << TYPE_NAME(int) << std::endl;
    std::cout << TYPE_NAME(int &) << std::endl;
    std::cout << (typeid(int) == typeid(int &)) << std::endl;
    // (2) In all cases, cv-qualifiers are ignored by typeid 
    //     (that is, typeid(T)==typeid(const T)) 
    std::cout << TYPE_NAME(const int) << std::endl;
    std::cout << (typeid(int) == typeid(const int)) << std::endl;

    PAUSE();
    return 0;
}

// References:
// http://en.cppreference.com/w/cpp/language/typeid
// Ongoing-Study/cpp/C++11/type_traits
