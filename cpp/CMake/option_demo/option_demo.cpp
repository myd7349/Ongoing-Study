// Happy 7.7.

#include <iostream>


int main()
{
#ifdef OLD_SCHOOL_STYLE
    std::cout << "Hello, school!\n";
#else
    std::cout << "Hello, world!\n";
#endif

    return 0;
}