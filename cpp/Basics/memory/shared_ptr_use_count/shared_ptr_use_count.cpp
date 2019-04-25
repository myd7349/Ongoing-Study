#include <iostream>
#include <memory>


int main()
{
    std::shared_ptr<int> p;

    {
        p = std::shared_ptr<int>(new int);
        std::cout << p.use_count() << std::endl;
    }

    std::cout << p.use_count() << std::endl;

    return 0;
}


// References:
// https://stackoverflow.com/questions/11920659/shared-ptr-and-use-count
// Ruminations on C++, Ch6
