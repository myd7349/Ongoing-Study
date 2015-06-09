// 2015-06-09T08:48+08:00
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <type_traits>

#include "../../common.h"

#ifndef USE_BLACK_MAGIC
# define USE_BLACK_MAGIC (1)
#endif

#if USE_BLACK_MAGIC
# include <malloc.h>
#endif

template <std::size_t N> struct Sizer { char e[N]; };
template <typename T, std::size_t N>
Sizer<N> CountOfHelper_(T (&)[N]);
#define COUNT_OF(arr) (sizeof(CountOfHelper_(arr).e))

int main()
{
    int arr[] {1, 2, 3, 4, 5};
    int v2d[][3] = {{1, 2, 3}, {4, 5, 6}};

    // 0. std::extent from C++11
    std::cout << std::extent<decltype(arr)>::value << std::endl;
    std::cout << std::extent<decltype(v2d), 0>::value
              << ","
              << std::extent<decltype(v2d), 1>::value
              << std::endl;

    // 1. ARRAYSIZE from common.h
    std::cout << ARRAYSIZE(arr) << std::endl;
    std::cout << ARRAYSIZE(v2d)
              << ","
              << ARRAYSIZE(v2d[0])
              << std::endl;

    // 2. COUNT_OF from stackoverflow
    std::cout << COUNT_OF(arr) << std::endl;
    std::cout << COUNT_OF(v2d)
              << ","
              << COUNT_OF(v2d[0])
              << std::endl;

#if USE_BLACK_MAGIC
    // 3. Black magic from Yangff at zhihu.com
    int *parr = new int[10];
# ifdef _WIN32
    std::cout << _msize(parr) / sizeof(*parr) << std::endl;
# else
    std::cout << malloc_usable_size(parr) / sizeof(*parr) << std::endl;
# endif
    delete[] parr;
#endif

    return 0;
}
// References:
// http://www.zhihu.com/question/23727596
// [ARRAYSIZE C++ macro: how does it work?](http://stackoverflow.com/questions/4064134/arraysize-c-macro-how-does-it-work)
