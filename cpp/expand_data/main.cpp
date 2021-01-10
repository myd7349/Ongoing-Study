// 2016-07-05T14:45+08:00
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "../common.h"


void ExpandData(const std::vector<int> &source, std::vector<int> &target, unsigned int width)
{
    target.resize(source.size() + 2 * width);
    std::copy_n(source.cbegin(), width, target.begin());
    std::copy(source.cbegin(), source.cend(), std::next(target.begin(), width));
    std::copy_n(std::prev(source.cend(), width), width,
                std::prev(target.end(), width));
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
