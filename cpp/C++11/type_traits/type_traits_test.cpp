// 2015-07-27T16:40+08:00
#include <iostream>

#ifndef CONFIG_USING_CXX11
# define CONFIG_USING_CXX11 (1)
#endif

#if CONFIG_USING_CXX11
# include <type_traits>
#endif

#include "../../common.h"
#include "../../uniform_typename/uniform_typename.h"

int main()
{
    int arr[] = { 1, 2, 3 };
    int *first = std::begin(arr);

#if CONFIG_USING_CXX11
    using ValueT = decltype(*first);
    using ValueT2 = std::remove_reference<ValueT>::type;

    std::cout << std::is_reference<ValueT>::value << std::endl; // true, why?
    std::cout << std::is_reference<ValueT2>::value << std::endl;
    std::cout << std::is_reference<std::iterator_traits<int *>::value_type>::value << std::endl;
    //assert(std::is_same<int &, ValueT>::value);
    //assert(std::is_same<int, ValueT2>::value);
#endif

    PAUSE();
    return 0;
}