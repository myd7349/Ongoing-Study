// 2014-05-26T17:20+08:00
#include <algorithm>
#include <iostream>
#include <iterator>

#include "nice_label.h"


template <typename InIt>
void printV(InIt begin, InIt end)
{
    std::ostream_iterator<typename InIt::value_type> oit(std::cout, " ");
    std::copy(begin, end, oit);
    // *oit = std::endl;
    std::cout << std::endl;
}

int main()
{
    std::vector<double> vticks;
    int nfrac;

    loose_label(2.03, 2.17, 9, vticks, nfrac);
    std::cout << nfrac << "\n";
    printV(vticks.begin(), vticks.end());

    loose_label(103, 249, 10, vticks, nfrac);
    std::cout << nfrac << "\n";
    printV(vticks.begin(), vticks.end());

    return 0;
}
