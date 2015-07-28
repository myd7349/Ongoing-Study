// 2015-07-27T14:39+08:00
#ifndef KAHAN_SUM_H_
#define KAHAN_SUM_H_

#include <algorithm>
#include <iterator>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>


template <typename InIt>
typename std::iterator_traits<InIt>::value_type kahan_sum(InIt first, InIt last)
{
    using ValueT = typename std::iterator_traits<InIt>::value_type;
    namespace Acc = boost::accumulators;
    Acc::accumulator_set<ValueT, Acc::stats<Acc::tag::sum_kahan>> acc;
    std::for_each(first, last, [&] (ValueT value) { acc(value); });

    return Acc::sum_kahan(acc);
}

#endif // KAHAN_SUM_H_

// References:
// Ongoing-study/cpp/C++11/type_traits
