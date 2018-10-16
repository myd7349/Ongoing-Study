#pragma once

#include <algorithm>
#include <cctype>
#include <string>


// trim from start (in place)
template <typename CharT>
static inline void TrimLeft(std::basic_string<CharT> &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}


// trim from end (in place)
template <typename CharT>
static inline void TrimRight(std::basic_string<CharT> &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}



// trim from both ends (in place)
template <typename CharT>
static inline void Trim(std::basic_string<CharT> &s) {
    TrimLeft(s);
    TrimRight(s);
}


template <typename CharT>
static inline void ToLower(std::basic_string<CharT> &s) {
    std::transform(s.begin(), s.end(), s.begin(), std::tolower);
}


template <typename CharT>
static inline void ToUpper(std::basic_string<CharT> &s) {
    std::transform(s.begin(), s.end(), s.begin(), std::toupper);
}


// References:
// Ongoing-Study/cpp/strutils.hpp
// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
