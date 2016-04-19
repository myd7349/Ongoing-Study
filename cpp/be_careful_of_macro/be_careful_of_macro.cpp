// 2014-06-24T15:28+08:00
// http://stackoverflow.com/questions/5416414/signed-unsigned-comparisons
// http://www.zhihu.com/question/25870045/answer/31609883
#include <algorithm>
#include <iostream>

#define MIN(a, b) ((a)<(b)?(a):(b))

#ifdef min
#  undef min
#endif

int main()
{
    std::cout << MIN(-1, 456U) << std::endl; // 456
    std::cout << MIN(-1L, 456U) << std::endl; // 456
    std::cout << std::min<int>(-1, 456U) << std::endl; // -1
    std::cout << std::min<unsigned int>(-1, 456U) << std::endl; // 456

    double this_is_an_array[] = { 42, 42 };
    // error: ISO C++ forbids comparison between pointer and integer
    //std::cout << MIN(this_is_an_array, 100) << std::endl; // Oops!
    // In VS2010, however, ...

    return 0;
}
