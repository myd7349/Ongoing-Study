// 2015-03-22T18:36+08:00
#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include <algorithm>
#include <iterator>
#include <vector>

#ifndef NDEBUG
# include <iostream>
# include "print_seq.hpp"
#endif

template <typename RandIter, typename SortPred>
RandIter _MergeSort(RandIter first, RandIter mid, RandIter last, SortPred pred)
{
    if (first < mid) { // At least two elements
        // Divide and conquer
        _MergeSort(first, first + (mid - first) / 2, mid, pred);
        _MergeSort(mid, mid + (last - mid) / 2, last, pred);

        // Merge
        using ValueT = typename std::iterator_traits<RandIter>::value_type;
        std::vector<ValueT> part1(first, mid);
        std::vector<ValueT> part2(mid, last);
        std::merge(part1.begin(), part1.end(), part2.begin(), part2.end(), first, pred);

#ifndef NDEBUG
        std::cout << "[ ";
        PrintSeq(first, mid, false);
        std::cout << "]" << " + [ ";
        PrintSeq(mid, last, false);
        std::cout << "] --> [ ";
        PrintSeq(first, last, false);
        std::cout << "]\n";
#endif
    }

    return first;
}

// Two-way merge sort
// O(nlgn)
template <typename RanIt, typename Pred>
RanIt MergeSort(RanIt first, RanIt last, Pred cmp)
{
#ifndef NDEBUG
    std::cout << __func__ << ": ";
    PrintSeq(first, last);
#endif
    return _MergeSort(first, first + (last - first) / 2, last, cmp);
}


#endif // MERGE_SORT_H_

// References:
// http://staff.ustc.edu.cn/~lszhuang/alg/
