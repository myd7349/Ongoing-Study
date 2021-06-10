// 2016-11-26T17:00+08:00
#ifndef SPLIT_HPP_
#define SPLIT_HPP_

#include <cassert>
//#include <sstream>
#include <string>


// split("a,b,,c,", ",", true) -> <a><b><><c><>
// split("a,b,,c,", ",", false) -> <a><b><c>
// split("", "") -> <> | QString().split("") -> <><>
// split("", "abc") -> <>
// split("abc", "") -> <abc> | QString("abc").split("") -> <><abc><>
template <typename ResultList, typename CharT>
ResultList split(const std::basic_string<CharT> &s,
    const std::basic_string<CharT> &delimiter, bool keepEmptyParts = true)
{
    ResultList slist;

    // If delimiter.empty():
    //   pos = s.find(delimiter, start);
    // pos will be 0.
    if (delimiter.empty()) {
        slist.push_back(s);
        return slist;
    }


    typename std::basic_string<CharT>::size_type start = 0;
    typename std::basic_string<CharT>::size_type pos;

    std::basic_string<CharT> part;

    if (delimiter.length() == 1) {
        CharT ch = delimiter[0];

        // Hope that:
        //   find(std::basic_string<CharT>, CharT ch)
        // will be faster than:
        //   find(std::basic_string<CharT>, std::basic_string<CharT>)
        while ((pos = s.find(ch, start)) != s.npos) { // Use strchr/wcschr instead?
            part = s.substr(start, pos - start);

            if (!part.empty() || keepEmptyParts)
                slist.push_back(part);

            start = pos + delimiter.length();
        }
    } else {
        while ((pos = s.find(delimiter, start)) != s.npos) { // Use strstr/wcsstr instead?
            part = s.substr(start, pos - start);

            if (!part.empty() || keepEmptyParts)
                slist.push_back(part);

            start = pos + delimiter.length();
        }
    }

    if (start != s.length() || keepEmptyParts)
        slist.push_back(s.substr(start));

    return slist;
}


template <typename ResultList, typename CharT>
inline ResultList split(const std::basic_string<CharT> &s,
    const CharT *delimiter, bool keepEmptyParts = true)
{
    assert(delimiter != nullptr);
    return split<ResultList>(s, std::basic_string<CharT>(delimiter), keepEmptyParts);
}


template <typename ResultList, typename CharT>
inline ResultList split(const CharT *s, const CharT *delimiter, bool keepEmptyParts = true)
{
    assert(s != nullptr);
    return split<ResultList>(std::basic_string<CharT>(s), delimiter, keepEmptyParts);
}


template <typename ResultList, typename CharT>
inline ResultList split(const std::basic_string<CharT> &s, CharT ch, bool keepEmptyParts = true)
{
#if 0
    ResultList slist;

    std::basic_istringstream<CharT> ss(s);
    std::basic_string<CharT> item;
    while (std::getline(ss, item, ch))
        slist.push_back(item);

    return slist;
#endif

    return split<ResultList>(s, std::basic_string<CharT>(1, ch), keepEmptyParts);
}


template <typename ResultList, typename CharT>
inline ResultList split(const CharT *s, CharT ch, bool keepEmptyParts = true)
{
    return split<ResultList>(std::basic_string<CharT>(s), ch, keepEmptyParts);
}


// split_by_tokens("a,b-,c,", ",-", true) -> <a><b><><c><>
// split_by_tokens("a,b-,c,", ",-", false) -> <a><b><c>
template <typename ResultList, typename CharT>
ResultList split_by_tokens(const std::basic_string<CharT> &s,
    const std::basic_string<CharT> &tokens, bool keepEmptyParts = true)
{
    if (tokens.length() == 1)
        return split<ResultList>(s, tokens, keepEmptyParts);

    ResultList slist;

    typename std::basic_string<CharT>::size_type start = 0;
    typename std::basic_string<CharT>::size_type pos;

    std::basic_string<CharT> part;

    // If delimiter.empty():
    //   pos = s.find_first_of(delimiter, start);
    // pos will be s.npos.
    while ((pos = s.find_first_of(tokens, start)) != s.npos) { // strtok
        part = s.substr(start, pos - start);

        if (!part.empty() || keepEmptyParts)
            slist.push_back(part);

        start = pos + 1;
    }

    if (start != s.length() || keepEmptyParts)
        slist.push_back(s.substr(start));

    return slist;
}


template <typename ResultList, typename CharT>
inline ResultList split_by_tokens(const std::basic_string<CharT> &s,
    const CharT *tokens, bool keepEmptyParts = true)
{
    assert(tokens != nullptr);
    return split_by_tokens<ResultList>(s, std::basic_string<CharT>(tokens), keepEmptyParts);
}


template <typename ResultList, typename CharT>
inline ResultList split_by_tokens(const CharT *s, const CharT *tokens, bool keepEmptyParts = true)
{
    assert(s != nullptr);
    return split_by_tokens<ResultList>(std::basic_string<CharT>(s), tokens, keepEmptyParts);
}


#endif // SPLIT_HPP_

// References:
// [Split a string in C++?](http://stackoverflow.com/questions/236129/split-a-string-in-c)
// Qt:QString::split
// https://www.zhihu.com/question/36642771
