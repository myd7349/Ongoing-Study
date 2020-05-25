#include <iostream>

#include "handle.hpp"


int main()
{
    {
        HandlePtr h1(10);
        HandlePtr h2 = h1;
        std::cout << h1.use_count() << std::endl;
        h2.x(42);
        std::cout << h1.x() << std::endl;
        std::cout << h1.use_count() << std::endl;
    }

    {
        HandleValue h1(10);
        HandleValue h2 = h1;
        std::cout << h1.use_count() << std::endl;
        h2.x(42);
        std::cout << h1.x() << std::endl;
        std::cout << h1.use_count() << std::endl;
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/11920659/shared-ptr-and-use-count
// Ruminations on C++, Ch6, Ch7
