// 2016-11-25T10:20+08:00
#ifndef STRUTILS_H_
#define STRUTILS_H_

#include <algorithm>
#include <cctype>
#include <string>

template <typename CharT, typename Pred>
std::basic_string<CharT> ChangeCase(const std::basic_string<CharT> &s, Pred pred)
{
    std::basic_string<CharT> result(s);
    std::transform(result.begin(), result.end(), result.begin(), pred);
    return result;
}

template <typename CharT>
inline std::basic_string<CharT> ToLower(const std::basic_string<CharT> &s)
{
    return ChangeCase(s, ::tolower);
}

template <typename CharT>
inline std::basic_string<CharT> ToUpper(const std::basic_string<CharT> &s)
{
    return ChangeCase(s, ::toupper);
}

template <typename CharT, typename Pred>
void ChangeCaseInPlace(std::basic_string<CharT> &s, Pred pred)
{
    std::transform(s.begin(), s.end(), s.begin(), pred);
}

template <typename CharT>
inline void ToLowerInPlace(std::basic_string<CharT> &s)
{
    ChangeCaseInPlace(s, ::tolower);
}

template <typename CharT>
inline void ToUpperInPlace(std::basic_string<CharT> &s)
{
    ChangeCaseInPlace(s, ::toupper);
}

#endif // STRUTILS_H_

// References:
// [How to convert std::string to lower case?](http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case)
