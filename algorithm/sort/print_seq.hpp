// 2015-03-22T21:07+08:00
#ifndef PRINT_SEQ_H_
#define PRINT_SEQ_H_

#include <algorithm>
#include <iostream>
#include <iterator>

template <typename InputIter>
void PrintSeq(InputIter first, InputIter last, bool newline = true)
{
    using ValueT = typename std::iterator_traits<InputIter>::value_type;
    std::copy(first, last, std::ostream_iterator<ValueT>(std::cout, " "));

    if (newline) {
        std::cout << std::endl;
    }
}

#endif // PRINT_SEQ_H_
