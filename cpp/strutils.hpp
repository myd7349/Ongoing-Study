// 2016-11-25T10:20+08:00
#ifndef STRUTILS_H_
#define STRUTILS_H_

#include <algorithm>
#include <cctype>
#include <functional>
#include <string>


template <typename CharT, typename Pred>
std::basic_string<CharT> &ChangeCaseInPlace(std::basic_string<CharT> &s, Pred pred)
{
    std::transform(s.begin(), s.end(), s.begin(), pred);
    return s;
}

template <typename CharT>
inline std::basic_string<CharT> &ToLowerInPlace(std::basic_string<CharT> &s)
{
    // Do not use std::tolower here, because <locale> also contains a
    // declaration of std::tolower.
    //return ChangeCaseInPlace(s, std::tolower);
    // Or, you may:
    return ChangeCaseInPlace(s, static_cast<int(*)(int)>(std::tolower));
    // You can also:
    //return ChangeCaseInPlace(s, ::tolower);
}

template <typename CharT>
inline std::basic_string<CharT> &ToUpperInPlace(std::basic_string<CharT> &s)
{
    return ChangeCaseInPlace(s, ::toupper);
}

template <typename CharT, typename Pred>
inline std::basic_string<CharT> ChangeCase(std::basic_string<CharT> s, Pred pred)
{
    return ChangeCaseInPlace(s, pred);
}

template <typename CharT>
inline std::basic_string<CharT> ToLower(std::basic_string<CharT> s)
{
    return ToLowerInPlace(s);
}

template <typename CharT>
inline std::basic_string<CharT> ToUpper(const std::basic_string<CharT> &s)
{
    return ToUpperInPlace(s);
}

template <typename CharT>
std::basic_string<CharT> &TrimLeftInPlace(std::basic_string<CharT> &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

template <typename CharT>
std::basic_string<CharT> &TrimRightInPlace(std::basic_string<CharT> &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

template <typename CharT>
inline std::basic_string<CharT> &TrimInPlace(std::basic_string<CharT> &s)
{
    return TrimRightInPlace(TrimLeftInPlace(s));
}

template <typename CharT>
inline std::basic_string<CharT> TrimLeft(std::basic_string<CharT> s)
{
    return TrimLeftInPlace(s);
}

template <typename CharT>
inline std::basic_string<CharT> TrimRight(std::basic_string<CharT> s)
{
    return TrimRightInPlace(s);
}

template <typename CharT>
inline std::basic_string<CharT> Trim(std::basic_string<CharT> s)
{
    return TrimInPlace(s);
}

inline bool ICompare(int lhs, int rhs)
{
    return tolower(lhs) == tolower(rhs);
}

template <typename CharT>
bool StringICompare(const std::basic_string<CharT> &lhs, const std::basic_string<CharT> &rhs)
{
    if (lhs.length() == rhs.length()) {
        return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), ICompare);
    } else {
        return false;
    }
}

template <typename CharT>
struct StringIHash {
    size_t operator()(const std::basic_string<CharT> &key) const {
        return hash_(ToLower(key));
    }

private:
    std::hash<std::basic_string<CharT>> hash_;
};


#endif // STRUTILS_H_

// References:
// [How to convert std::string to lower case?](http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case)
// [Case insensitive string comparison in C++](http://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c)
// [Case insensitive standard string comparison in C++ [duplicate]](http://stackoverflow.com/questions/23943728/case-insensitive-standard-string-comparison-in-c)
// [Remove spaces from std::string in C++](http://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c)
// [What's the best way to trim std::string?](http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
// https://github.com/nu774/qaac/blob/master/strutil.h

