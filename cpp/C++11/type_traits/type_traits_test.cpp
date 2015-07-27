// 2015-07-27T16:40+08:00
#include "../../common.h"
#include "../../uniform_typename/uniform_typename.h"

#ifndef CONFIG_USING_CXX11
# define CONFIG_USING_CXX11 (1)
#endif

#if CONFIG_USING_CXX11
# include <type_traits>
#endif

int main()
{
    std::cout << TYPE_NAME(int &) << std::endl; // int? int &?
    std::cout << TYPE_NAME(const int &) << std::endl; // ??
    int arr[] = { 1, 2, 3 };
    int *first = std::begin(arr);

#if CONFIG_USING_CXX11
    assert(std::is_reference<decltype(*first)>::value); // true, why?
    assert(!std::is_reference<std::iterator_traits<int *>::value_type>::value); // false
#endif

    PAUSE();
    return 0;
}