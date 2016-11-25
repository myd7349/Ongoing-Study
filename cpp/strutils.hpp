// 2016-11-25T10:20+08:00
#ifndef STRUTILS_H_
#define STRUTILS_H_

#include <algorithm>
#include <cctype>
#include <string>

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

template <typename CharT, typename Pred>
std::basic_string<CharT> ChangeCase(const std::basic_string<CharT> &s, Pred pred)
{
    std::basic_string<CharT> result(s);
    ChangeCaseInPlace(result, pred);
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
void LStripInPlace(std::basic_string<CharT> &s, Pred pred)
{

}

template <typename CharT, typename Pred>
void RStripInPlace(std::basic_string<CharT> &s, Pred pred)
{

}

template <typename CharT, typename Pred>
void StripInPlace(std::basic_string<CharT> &s, Pred pred)
{

}

template <typename CharT, typename Pred>
std::basic_string<CharT> LStrip(const std::basic_string<CharT> &s, Pred pred)
{

}

template <typename CharT, typename Pred>
std::basic_string<CharT> RStrip(const std::basic_string<CharT> &s, Pred pred)
{

}

template <typename CharT, typename Pred>
std::basic_string<CharT> Strip(const std::basic_string<CharT> &s, Pred pred)
{

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


#endif // STRUTILS_H_

// References:
// [How to convert std::string to lower case?](http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case)
// [Case insensitive string comparison in C++](http://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c)
// [Case insensitive standard string comparison in C++ [duplicate]](http://stackoverflow.com/questions/23943728/case-insensitive-standard-string-comparison-in-c)

