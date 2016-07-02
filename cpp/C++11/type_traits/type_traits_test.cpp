// 2015-07-27T16:40+08:00
#include <array>
#include <iostream>
#include <type_traits>
#include <vector>

#include "../../common.h"
#include "../../uniform_typename/uniform_typename.h"

struct A
{
    int a;
    int b;
    int c;
};

struct B
{
};

class C
{
public:
    int a;
    int b;
};

struct D
{
    std::array<int, 32> data;
};

struct E
{
    E() : a(-1) {}
    int a;
};

int main()
{
    int arr[] = { 1, 2, 3 };
    int *first = std::begin(arr);

    using ValueT = decltype(*first);
    using ValueT2 = std::remove_reference<ValueT>::type;

    std::cout << std::is_reference<ValueT>::value << std::endl; // true, why?
    std::cout << std::is_reference<ValueT2>::value << std::endl;
    std::cout << std::is_reference<std::iterator_traits<int *>::value_type>::value << std::endl;

    // is_same
#if !defined(_MSC_VER) || _MSC_VER > 1800
    //assert(std::is_same<int &, ValueT>::value);
    //assert(std::is_same<int, ValueT2>::value);
#endif
    typedef int* value_type;
    std::cout << std::is_same<const value_type &, int* const&>::value << std::endl;

    // 
    std::vector<int> ivec(10, 1);
    std::vector<bool> bvec(10, true);
    std::cout << TYPE_NAME(decltype(*ivec.begin())) << std::endl;
    std::cout << TYPE_NAME(decltype(*bvec.begin())) << std::endl;

    // POD
    std::cout << std::is_pod<A>::value << std::endl;
    std::cout << std::is_pod<B>::value << std::endl;
    std::cout << std::is_pod<C>::value << std::endl;
    std::cout << std::is_pod<D>::value << std::endl;
    std::cout << std::is_pod<E>::value << std::endl;

    // trivial
    std::cout << std::endl;
    std::cout << std::is_trivial<A>::value << std::endl;
    std::cout << std::is_trivial<B>::value << std::endl;
    std::cout << std::is_trivial<C>::value << std::endl;
    std::cout << std::is_trivial<D>::value << std::endl;
    std::cout << std::is_trivial<E>::value << std::endl;

    // trivially copiable
    std::cout << std::endl;
    std::cout << std::is_trivially_copyable<A>::value << std::endl;
    std::cout << std::is_trivially_copyable<B>::value << std::endl;
    std::cout << std::is_trivially_copyable<C>::value << std::endl;
    std::cout << std::is_trivially_copyable<D>::value << std::endl;
    std::cout << std::is_trivially_copyable<E>::value << std::endl;

    PAUSE();
    return 0;
}

// References:
// [How to declare the value of an iterator through decltype](http://stackoverflow.com/questions/15560912/how-to-declare-the-value-of-an-iterator-through-decltype)