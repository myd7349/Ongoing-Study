// 2014-08-15T17:10+08:00
// `iota`, not `itoa`.
//
// 2015-02-12T09:28+08:00
// https://github.com/miloyip/itoa-benchmark
// >Note that itoa() is not a standard function in C and C++, but provided by some compilers.
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <numeric>

template <typename T>
class NumberGenerator
{
public:
    NumberGenerator(T start, T stride)
        : _start(start), _stride(stride) {}
    T &&operator()() {
        T tmp = _start;
        _start += _stride;
        return std::move(tmp);
    }
private:
    T _start;
    T _stride;
};

template <typename InIt>
void print(InIt first, InIt last, bool newline = true)
{
    typedef typename std::iterator_traits<InIt>::value_type _T;
    std::copy(first, last, std::ostream_iterator<_T>(std::cout, " "));

    if (newline) {
        std::cout << std::endl;
    }
}

int main()
{
    std::array<int, 6> arr /*{1, 2, 3, 4, 5, 6}*/;

    int count = 0;
    for (auto &i : arr) {
        i = ++count;
    }
    print(arr.begin(), arr.end());

    std::iota(arr.begin(), arr.end(), 1);
    print(arr.begin(), arr.end());

    std::generate(arr.begin(), arr.end(), NumberGenerator<int>(1, 1));
    print(arr.begin(), arr.end());

    // Note that, when using std::iota, you can not specify a step size.

    return 0;
}
// References:
// [What does iota of std::iota stand for?](http://stackoverflow.com/questions/9244879/what-does-iota-of-stdiota-stand-for)
// [iota](http://www.sgi.com/tech/stl/iota.html)
