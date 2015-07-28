// 2015-07-27T11:08+08:00
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>

#include "../../../common.h"
#include "kahan_sum.hpp"

int main()
{
    std::vector<double> nums(10, 0.1);

    double res = std::accumulate(nums.cbegin(), nums.cend(), 0.0); // std::plus
    std::printf("%.20f, %.1f\n", res, res);

    res = kahan_sum(nums.cbegin(), nums.cend());
    std::printf("%.20f, %.1f\n", res, res);

    PAUSE();
    return 0;
}

// Output(My platform: Win7 x64 + VS2013):
// 0.99999999999999989000, 1.0
// 1.00000000000000000000, 1.0

// References:
// [为什么C语言中浮点数(double/float)没办法进行等于关系逻辑运算？](http://www.zhihu.com/question/32304267)
// [Difference between float and double](http://stackoverflow.com/questions/2386772/difference-between-float-and-double)
// [Kahan summation algorithm](https://en.wikipedia.org/wiki/Kahan_summation_algorithm)
// [sum of small double numbers c++](http://stackoverflow.com/questions/10330002/sum-of-small-double-numbers-c)
// https://github.com/myd7349/Ongoing-Study/blob/master/algorithm/math/KahanSummation.py
