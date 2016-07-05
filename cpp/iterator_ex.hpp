// 2016-07-05T14:39+08:00
#ifndef ITERATOR_EX_HPP_
#define ITERATOR_EX_HPP_

#include <iterator>

template <typename InputIterator, typename Distance>
InputIterator Advance(InputIterator it, Distance offset)
{
    InputIterator targetIterator = it;
    std::advance(targetIterator, offset);
    return targetIterator;
}

#endif // ITERATOR_EX_HPP_
