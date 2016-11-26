// 2016-11-26T17:00+08:00
#ifndef SPLIT_HPP_
#define SPLIT_HPP_

#include <cassert>
#include <sstream>
#include <string>
#include <vector>


#define string_list std::vector<std::basic_string<CharT>>


// Behaves like strtok
template <typename CharT>
string_list split_by_tokens(const std::basic_string<CharT> &s, const std::basic_string<CharT> &tokens)
{
    string_list slist;

    typename std::basic_string<CharT>::size_type start = 0;
    typename std::basic_string<CharT>::size_type pos;

    while ((pos = s.find_first_of(tokens, start)) != s.npos) {
        slist.push_back(s.substr(start, pos - start));
        start = pos + 1;
    }

    if (start < s.length())
        slist.push_back(s.substr(start));

    return slist;
}

template <typename CharT>
inline string_list split_by_tokens(const std::basic_string<CharT> &s, const CharT *tokens)
{
    assert(tokens != nullptr);
    return split_by_tokens(s, std::basic_string<CharT>(tokens));
}

template <typename CharT>
inline string_list split_by_tokens(const CharT *s, const CharT *tokens)
{
    assert(s != nullptr);
    return split_by_tokens(std::basic_string<CharT>(s), tokens);
}

// Use strstr/wcsstr instead?
template <typename CharT>
string_list split(const std::basic_string<CharT> &s, const std::basic_string<CharT> &delimiter)
{
    string_list slist;

    typename std::basic_string<CharT>::size_type start = 0;
    typename std::basic_string<CharT>::size_type pos;

    while ((pos = s.find(delimiter, start)) != s.npos) {
        slist.push_back(s.substr(start, pos - start));
        start = pos + delimiter.length();
    }

    if (start < s.length())
        slist.push_back(s.substr(start));

    return slist;
}

template <typename CharT>
inline string_list split(const std::basic_string<CharT> &s, const CharT *delimiter)
{
    assert(delimiter != nullptr);
    return split(s, std::basic_string<CharT>(delimiter));
}

template <typename CharT>
inline string_list split(const CharT *s, const CharT *delimiter)
{
    assert(s != nullptr);
    return split(std::basic_string<CharT>(s), delimiter);
}

// Use strchr/wcschr instead?
template <typename CharT>
string_list split(const std::basic_string<CharT> &s, CharT ch)
{
    string_list slist;

    std::basic_istringstream<CharT> ss(s);
    std::basic_string<CharT> item;
    while (std::getline(ss, item, ch))
        slist.push_back(item);

    return slist;
}

template <typename CharT>
inline string_list split(const CharT *s, CharT ch)
{
    return split(std::basic_string<CharT>(s), ch);
}

#undef string_list

#endif // SPLIT_HPP_

// References:
// [Split a string in C++?](http://stackoverflow.com/questions/236129/split-a-string-in-c)
