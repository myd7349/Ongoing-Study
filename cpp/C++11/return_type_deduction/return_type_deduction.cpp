// 2015-07-27T15:05+08:00
#include <iostream>
#include <iterator>
#include <type_traits>

#include "../../common.h"
#include "../../uniform_typename/uniform_typename.h"

template <typename T>
inline std::ostream &dump(std::ostream &out, T obj)
{
    out << "Type: " << TYPE_NAME(obj) << ", value: " << obj;
    return out;
}

template <typename T0, typename T1>
auto add(T0 lhs, T1 rhs) -> decltype(lhs + rhs)
{
    return lhs + rhs;
}

template <typename InIt>
// -1.
//auto accu(InIt first, InIt last)
// Not supported by C++11.
// 0.
typename std::iterator_traits<InIt>::value_type accu(InIt first, InIt last) // OK
// 1.
//auto accu(InIt first, InIt last) -> typename std::iterator_traits<InIt>::value_type // OK
// 2.
//auto accu(InIt first, InIt last) -> decltype(typename std::iterator_traits<InIt>::value_type)
// VS2013: error C2893: Failed to specialize function template 'unknown-type accu(InIt,InIt)'
// decltype(entity/expression) is OK; decltype(type), however, is wrong. That is, decltype specifier
// can not work with a type.
// 3.
//decltype(*first) accu(InIt first, InIt last)
// VS2013: error C2893: Failed to specialize function template 'unknown-type accu(InIt,InIt)'
// 4.
//auto accu(InIt first, InIt last) -> decltype(*first)
// Not OK!!!
// From this test: Ongoing-study/cpp/C++11/type_traits
// we know that, we shouldn't deduce the value type from `decltype(*iter)`.
{
#if 0
    using ValueT = decltype(*first);
    std::cout << TYPE_NAME(ValueT) << std::endl;
#else
    using ValueT = std::iterator_traits<InIt>::value_type;
    std::cout << TYPE_NAME(const int &) << std::endl;
#endif

    ValueT result = ValueT();
    while (first != last) {
        result += *first++;
    }
    return result;
}

int main()
{
    dump(std::cout, add(1, 2)) << std::endl;
    dump(std::cout, add(1.0, 3)) << std::endl;

    int arr[] = { 1, 2, 3, 4, 5 };
    dump(std::cout, accu(std::begin(arr), std::end(arr))) << std::endl;

    PAUSE();
    return 0;
}

// References:
// [C++ template 为什么不能推导返回值类型？](http://www.zhihu.com/question/24671324)
// [Omit return type in C++11](http://stackoverflow.com/questions/4523617/omit-return-type-in-c11)
// [When should I use C++14 automatic return type deduction?](http://stackoverflow.com/questions/15737223/when-should-i-use-c14-automatic-return-type-deduction)
// [Deducing value type from iterator for return type of template function](http://stackoverflow.com/questions/30354455/deducing-value-type-from-iterator-for-return-type-of-template-function)
// [Can C++11 decltype be used to create a typedef for function pointer from an existing function?](http://stackoverflow.com/questions/13089067/can-c11-decltype-be-used-to-create-a-typedef-for-function-pointer-from-an-exis)
// Ongoing-study/cpp/C++11/type_traits