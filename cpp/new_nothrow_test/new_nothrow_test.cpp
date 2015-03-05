// 2014-11-19T15:36+08:00
#include <iostream>
#include <new> // for std::nothrow and nothrow allocation

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
