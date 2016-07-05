// 2016-07-05T14:45+08:00
#include <algorithm>
#include <iostream>
#include <vector>

#include "../common.h"
#include "../iterator_ex.hpp"

void ExpandData(const std::vector<int> &source, std::vector<int> &target, unsigned int width)
{
    target.resize(source.size() + 2 * width);
    std::copy_n(source.cbegin(), width, target.begin());
    std::copy(source.cbegin(), source.cend(), Advance(target.begin(), width));
    std::copy_n(Advance(source.cend(), -static_cast<int>(width)), width,
                Advance(target.end(), -static_cast<int>(width)));
}

int main()
{
    std::vector<int> source { 1, 2, 3, 4, 5, 6 };
    std::vector<int> expanded;

    ExpandData(source, expanded, 2);

    Println(source.cbegin(), source.cend());
    Println(expanded.cbegin(), expanded.cend());

    return 0;
}
