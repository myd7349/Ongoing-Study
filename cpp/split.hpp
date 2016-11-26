// 2016-11-26T17:00+08:00
#ifndef SPLIT_HPP_
#define SPLIT_HPP_

#include <cassert>
#include <cstring>
#include <stddef.h>
#include <string>
#include <vector>

#define USE_CXX11_FEATURES (0)

#if USE_CXX11_FEATURES
template <CharT>
using string_list = std::vector<std::basic_string<CharT>>;
#else
# define string_list std::vector<std::basic_string<CharT>>
#endif // USE_CXX11_FEATURES


// Behaves like strtok
template <typename CharT>
string_list split_by_tokens(const std::basic_string<CharT> &s, const std::basic_string<CharT> &tokens)
{
    string_list slist;

    size_t start = 0;
    size_t pos;

    while (start < s.length()) {
        pos = s.find_first_of(tokens, start);
        if (pos != s.npos) {
            slist.push_back(s.substr(start, pos - start));
            start = pos + 1;
        } else {
            slist.push_back(s.substr(start));
            break;
        }
    }

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

template <typename CharT>
string_list split(const std::basic_string<CharT> &s, const std::basic_string<CharT> &delimiter)
{

}

template <typename CharT>
inline string_list split(const std::basic_string<CharT> &s, const CharT *delimiter)
{
    return split(s, std::basic_string<CharT>(delimiter));
}

template <typename CharT>
string_list split(const std::basic_string<CharT> &s, CharT ch)
{
    string_list slist;



    return slist;
}


#endif // SPLIT_HPP_
