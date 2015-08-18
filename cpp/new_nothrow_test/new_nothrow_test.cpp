// 2014-11-19T15:36+08:00
#include <iostream>
#include <new> // for std::nothrow and nothrow allocation

// 2015-08-18T15:04+08:00
// Effective C++ 3rd Edition/Item 49:
// Using nothrow new guarantees only that operator new won't throw, not that an
//  expression like "new (std::nothrow) Widget" will never yield an exception.
//  In all likelihood, you will never have a need for nothrow new.


int main()
{
    if (int *x = new (std::nothrow) int(10)) {
        std::cout << *x << std::endl;
        delete x;
    } else {
        std::cout << (x == nullptr) << std::endl;
    }
    return 0;
}

