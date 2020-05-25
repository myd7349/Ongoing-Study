#include <cassert>
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
        h2.y(42);
        std::cout << h1.x() << std::endl;
        std::cout << h1.use_count() << std::endl;
        HandleValue h3 = h1;
        assert(h3.use_count() == 2);
        h3 = h2;
        assert(h1.use_count() == 1);
        assert(h2.use_count() == 2);
        assert(h3.use_count() == 2);
        h3.x(100);
        assert(h2.use_count() == 1);
        assert(h3.use_count() == 1);
        h3 = HandleValue(10, 10);
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/11920659/shared-ptr-and-use-count
// Ruminations on C++, Ch6, Ch7
