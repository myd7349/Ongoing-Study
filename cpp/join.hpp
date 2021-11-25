// 2015-10-19T15:14+08:00

#ifndef JOIN_H_
#define JOIN_H_

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

template <typename BidIt, typename CharT>
std::basic_string<CharT> join(BidIt first, BidIt last, const std::basic_string<CharT> &s)
{
    if (first == last)
        return std::basic_string<CharT>();
    
    using value_t = typename std::iterator_traits<BidIt>::value_type;

    std::basic_ostringstream<CharT> oss;
    BidIt back = std::prev(last);

    std::for_each(first, back, [&oss,s] (const value_t &val) { oss << val << s; });
    if (first != last)
        oss << *back;

    return oss.str();
}


template <typename BidIt, typename CharT>
std::basic_string<CharT> join(BidIt first, BidIt last, const CharT *s)
{
    return join(first, last, std::basic_string<CharT>(s));
}


template <typename BidIt, typename CharT>
std::basic_string<CharT> join(BidIt first, BidIt last, CharT c)
{
    //char ch = 'A';
    //std::string str(ch); // error
    //std::string str = ch; // error
    //std::string str; str += ch; // OK
    return join(first, last, std::basic_string<CharT>(1, c));
}

#endif // JOIN_H_


// References:
// https://github.com/imageworks/pystring/blob/master/pystring.h
// https://github.com/google/cpp-from-the-sky-down/blob/151c334647b52a4462d64cf7176893ddd29bb52f/string/string.cpp#L122-L126
