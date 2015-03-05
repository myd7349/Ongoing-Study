// 2014-08-12T17:06+08:00
#include <cstddef>
#include <iostream>
#include <typeinfo>

#include "../../uniform_typename/uniform_typename.h"

int main()
{
    // ISO C++11 5.3.4
    auto ch = new auto('C');
    std::cout << *ch << std::endl;
    delete ch;

    auto arr = new int[4] {1, 2, 3, 4};
    // error: no matching function for call to 'begin(int*&)'
    //for (auto i : arr) {
    //    std::cout << i << std::endl;
    //}
    delete[] arr;

    // 2014-12-02 16:17
    // C++11/14 Rocks Clang Edition Alex Korban P12
    // Variables declared with auto still have a static type just like any other variables.
    // The compiler needs to have enough information to figure the type out - and this is
    // provided by the initializing expression.
    const std::size_t SIZE = 4;
    // error: invalid use of 'auto'
    //auto arr2 = new auto[SIZE] {1, 2, 3, 4};
    //delete[] arr2;

    auto arr3 = new auto({1, 2, 3, 4});
    // error: cannot bind 'std::ostream
    // {aka std::basic_ostream<char>}' lvalue to
    // 'std::basic_ostream<char>&&'
    //for (std::size_t i = 0; i < 4; ++i) {
    //    std::cout << arr3[i] << std::endl;
    //}
    for (auto it = arr3->begin(); it != arr3->end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << TYPE_NAME(arr3) << std::endl;
    delete[] arr3;

    return 0;
}
