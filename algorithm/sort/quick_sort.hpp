// 2017-10-31T09:19+08:00
#ifndef QUICK_SORT_HPP_INCLUDED
#define QUICK_SORT_HPP_INCLUDED

#include <algorithm>
#include <functional>
#include <iterator>

#ifndef NDEBUG
# include <iostream>
# include "print_seq.hpp"
#endif


template <typename ForwardIt, typename BinaryPredicate>
void QuickSort(ForwardIt first, ForwardIt last, BinaryPredicate p)
{
    if (first == last)
        return;

    // Several ways to get `pivot`:
    // 1. 
    //auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto pivot = *first;
    // 2.
    //auto pivot = *(first + randint(0, last - first));
    // 3.
    //auto pivot1 = *(first + randint(0, last - first));
    //auto pivot2 = *(first + randint(0, last - first));
    //auto pivot3 = *(first + randint(0, last - first));
    //auto pivot = middle of pivot1, pivot2, pivot3.

    using ValueT = typename std::iterator_traits<ForwardIt>::value_type;
    ForwardIt middle1 = std::partition(first, last, [pivot](const ValueT &elem){ return elem < pivot; });
    ForwardIt middle2 = std::partition(middle1, last, [pivot](const ValueT &elem){ return !(pivot < elem); });

#ifndef NDEBUG
    std::cout << "[ ";
    PrintSeq(first, middle1, false);
    std::cout << "]" << " + pivots " << "[ ";
    PrintSeq(middle1, middle2, false);
    std::cout << "] --> [ ";
    PrintSeq(middle2, last, false);
    std::cout << "] --> [ ";
    PrintSeq(first, last, false);
    std::cout << "]\n";
#endif

    QuickSort(first, middle1, p);
    QuickSort(middle2, last, p);

#ifndef NDEBUG
        std::cout << "--> [ ";
        PrintSeq(first, middle1, false);
        std::cout << "]" << " + pivots " << "[ ";
        PrintSeq(middle1, middle2, false);
        std::cout << "] --> [ ";
        PrintSeq(middle2, last, false);
        std::cout << "] --> [ ";
        PrintSeq(first, last, false);
        std::cout << "]\n";
#endif
}


template <typename ForwardIt>
void QuickSort(ForwardIt first, ForwardIt last)
{
    QuickSort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>());
}

#endif // QUICK_SORT_HPP_INCLUDED

// References:
// Algorithms, 4th Edition, by Robert Sedgewick and Kevin Wayne
// http://en.cppreference.com/w/cpp/algorithm/partition
// Mastering Algorithms with C, Kyle London, 1999
