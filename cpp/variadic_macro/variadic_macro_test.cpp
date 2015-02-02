// 2015-02-02T13:17+08:00

#include <iostream>

#define CONFIG_USING_BOOST (0)
#include "../common.h"
#include "../variadic_macro.h"

#ifndef _MSC_VER
# include "../uniform_typename/uniform_typename.h"
# define HAHA(...) #__VA_ARGS__
# define TEST_HAHA(...) (void)(std::cout << TYPE_NAME(HAHA(__VA_ARGS__)) << "\t" << sizeof(HAHA(__VA_ARGS__)) << "\t" << HAHA(__VA_ARGS__) << std::endl)
#endif

int main()
{
#ifndef _MSC_VER
    TEST_HAHA();
    TEST_HAHA(1);
    TEST_HAHA(1, 2);
    TEST_HAHA(1, 2, 3);
#endif

    std::cout << VA_NARGS() << std::endl;
    std::cout << VA_NARGS(1) << std::endl;
    std::cout << VA_NARGS(1, 2) << std::endl;
    std::cout << VA_NARGS(1, 2, 3) << std::endl;

    PAUSE();
    return 0;
}
