// 2015-03-22T16:34+08:00
#ifndef INSERTION_SORT_H_
#define INSERTION_SORT_H_

#include <iterator>

#ifndef NDEBUG
# include <iostream>
# include "print_seq.hpp"
#endif

// O(n^2)
template <typename RandIter, typename SortPred>
RandIter InsertionSort(RandIter first, RandIter last, SortPred pred)
{
#ifndef NDEBUG
    std::cout << __func__ << ": ";
    PrintSeq(first, last);
#endif

    // For the input sequence [first, last), suppose the sub-sequence
    // [first, p) is always a sorted sequence. Then loop through
    // [p, last), and insert each element to the right place in range [first, p).
    for (RandIter p = first + 1; p < last; ++p) {
        // Now, just record down the element we are going to insert.
        typename std::iterator_traits<RandIter>::value_type temp = *p;

        // Find the right place where to insert element pointed by `p`.
        RandIter pos;
        for (pos = p - 1; pos >= first; --pos) {
            if (pred(temp, *pos)) {
                *(pos + 1) = *pos;
            } else {
                break;
            }
        }

        *(pos + 1) = temp;

#ifndef NDEBUG
        PrintSeq(first, last, false);
        std::cout << "\t[" << p - 1 - pos << "]\n";
#endif
    }

    return first;
}

#endif // INSERTION_SORT_H_

// References:
// http://staff.ustc.edu.cn/~lszhuang/alg/
