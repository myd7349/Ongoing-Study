// 2015-10-19T15:14+08:00

#ifndef JOIN_H_
#define JOIN_H_

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

template <typename BidIt, typename SplitterT, typename CharT = char>
std::basic_string<CharT> join(BidIt first, BidIt last, SplitterT s)
{
    using value_t = typename std::iterator_traits<BidIt>::value_type;

    std::basic_ostringstream<CharT> oss;
    BidIt back = std::prev(last);

    std::for_each(first, back, [&oss,s] (const value_t &val) { oss << val << s; });
    if (first != last)
        oss << *back;

    return oss.str();
}

#endif // JOIN_H_
