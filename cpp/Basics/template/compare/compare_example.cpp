#include <cstddef>
#include <cstring>
#include <iostream>

#include "../../../common.h"


template <typename T>
int compare(const T &x, const T &y)
{
    std::cout << "---- compare(const T &x, const T &y) ----\n";

    if (x < y)
        return -1;
    else if (y < x)
        return 1;
    else
        return 0;
}


template <std::size_t N, std::size_t M>
int compare(const char(&p1)[N], const char(&p2)[M])
{
    std::cout << "---- compare(const char(&p1)[N], const char(&p2)[M]) ----\n";

    return std::strcmp(p1, p2);
}


template <>
int compare(const char *const &p1, const char *const &p2)
{
    std::cout << "---- compare(const char *const &p1, const char *const &p2) ----\n";

    return std::strcmp(p1, p2);
}


int main()
{
    const char *p1 = "mom";
    const char *p2 = "hi";

    std::cout << compare(p1, p2) << std::endl;
    std::cout << compare("hi", "mom") << std::endl;

    PAUSE();

    return 0;
}


// References:
// C++ Primer, 5th Edition, 16.5 Template Specializations

/*
Output:
(clang, gcc 9.0)

---- compare(const char *const &p1, const char *const &p2) ----
5
---- compare(const char(&p1)[N], const char(&p2)[M]) ----
-5

Output:
(VS2017)
---- compare(const char *const &p1, const char *const &p2) ----
1
---- compare(const char(&p1)[N], const char(&p2)[M]) ----
-1
*/
