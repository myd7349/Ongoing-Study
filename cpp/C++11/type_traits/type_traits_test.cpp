// 2015-07-27T16:40+08:00
#include <iostream>
#include <type_traits>
#include <vector>

#include "../../common.h"
#include "../../uniform_typename/uniform_typename.h"

int main()
{
    int arr[] = { 1, 2, 3 };
    int *first = std::begin(arr);

    using ValueT = decltype(*first);
    using ValueT2 = std::remove_reference<ValueT>::type;

    std::cout << std::is_reference<ValueT>::value << std::endl; // true, why?
    std::cout << std::is_reference<ValueT2>::value << std::endl;
    std::cout << std::is_reference<std::iterator_traits<int *>::value_type>::value << std::endl;

#if !defined(_MSC_VER) || _MSC_VER > 1800
    assert(std::is_same<int &, ValueT>::value);
    assert(std::is_same<int, ValueT2>::value);
#endif

    // 
    std::vector<int> ivec(10, 1);
    std::vector<bool> bvec(10, true);
    std::cout << TYPE_NAME(decltype(*ivec.begin())) << std::endl;
    std::cout << TYPE_NAME(decltype(*bvec.begin())) << std::endl;

    PAUSE();
    return 0;
}

// References:
// [How to declare the value of an iterator through decltype](http://stackoverflow.com/questions/15560912/how-to-declare-the-value-of-an-iterator-through-decltype)