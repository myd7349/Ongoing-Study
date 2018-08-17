// Happy 7.7.

#include <iostream>

#ifndef OLD_SCHOOL_STYLE
# define OLD_SCHOOL_STYLE (0)
#endif


int main()
{
#if OLD_SCHOOL_STYLE
    std::cout << "Hello, school!\n";
#else
    std::cout << "Hello, world!\n";
#endif

    return 0;
}