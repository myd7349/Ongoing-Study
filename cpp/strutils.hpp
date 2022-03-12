// 2016-11-25T10:20+08:00
#ifndef STRUTILS_H_
#define STRUTILS_H_

#include <algorithm>
#include <cassert>
#include <cctype>
#include <functional>
#include <locale>
#include <string>

#ifdef HAS_CODECVT
# include <codecvt>
#endif


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
    // [](char ch){ return !std::isspace<char>(ch , std::locale::classic()); }
    // std::isspace's MSVC implementation may contains this:
    // assert(c >= -1 && c <= 255);
    if (sizeof(CharT) == 1)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    }
    else
    {
        // For VS2010:
        // CString::Trim
        //s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        //    std::not1(std::ptr_fun<int, int>(std::iswspace))));
        s.erase(s.begin(),
            std::find_if(s.begin(), s.end(),
                [](CharT ch)
                {
                    return !std::isspace<CharT>(ch , std::locale::classic());
                }));
    }
    
    return s;
}

template <typename CharT>
std::basic_string<CharT> &TrimRightInPlace(std::basic_string<CharT> &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](CharT ch)
        {
            return !std::isspace<CharT>(ch , std::locale::classic());
        }).base(), s.end());
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

template <typename CharT>
bool StartsWith(const std::basic_string<CharT> &lhs, const std::basic_string<CharT> &rhs)
{
    if (rhs.empty())
        return true;

    if (lhs.length() < rhs.length())
        return false;

    return lhs.compare(0, rhs.length(), rhs) == 0;
}

template <typename CharT>
bool StartsWith(const std::basic_string<CharT> &lhs, const CharT *rhs)
{
    assert(rhs != nullptr);
    return StartsWith(lhs, std::basic_string<CharT>(rhs));
}

template <typename CharT>
bool StartsWith(const std::basic_string<CharT> &lhs, CharT ch)
{
    return StartsWith(lhs, std::basic_string<CharT>(1, ch));
}

template <typename CharT>
bool StartsWith(const CharT *str, const std::basic_string<CharT> &rhs)
{
    assert(str != nullptr);
    return StartsWith(std::basic_string<CharT>(str), rhs);
}

template <typename CharT>
bool StartsWith(const CharT *str, const CharT *rhs)
{
    assert(str != nullptr);
    return StartsWith(std::basic_string<CharT>(str), rhs);
}

template <typename CharT>
bool StartsWith(const CharT *str, CharT ch)
{
    assert(str != nullptr);
    return StartsWith(std::basic_string<CharT>(str), ch);
}

template <typename CharT>
bool EndsWith(const std::basic_string<CharT> &lhs, const std::basic_string<CharT> &rhs)
{
    if (rhs.empty())
        return true;

    if (lhs.length() < rhs.length())
        return false;

    return lhs.compare(lhs.length() - rhs.length(), rhs.length(), rhs) == 0;
}

template <typename CharT>
bool EndsWith(const std::basic_string<CharT> &lhs, const CharT *rhs)
{
    assert(rhs != nullptr);
    return EndsWith(lhs, std::basic_string<CharT>(rhs));
}

template <typename CharT>
bool EndsWith(const std::basic_string<CharT> &lhs, CharT ch)
{
    return EndsWith(lhs, std::basic_string<CharT>(1, ch));
}

template <typename CharT>
bool EndsWith(const CharT *str, const std::basic_string<CharT> &rhs)
{
    assert(str != nullptr);
    return EndsWith(std::basic_string<CharT>(str), rhs);
}

template <typename CharT>
bool EndsWith(const CharT *str, const CharT *rhs)
{
    assert(str != nullptr);
    return EndsWith(std::basic_string<CharT>(str), rhs);
}

template <typename CharT>
bool EndsWith(const CharT *str, CharT ch)
{
    assert(str != nullptr);
    return EndsWith(std::basic_string<CharT>(str), ch);
}

#ifdef HAS_CODECVT
std::string ws2s(const std::wstring &str)
{
    return (std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>()).to_bytes(str);
}
#endif

#endif // STRUTILS_H_

// References:
// [How to convert std::string to lower case?](http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case)
// [Case insensitive string comparison in C++](http://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c)
// [Case insensitive standard string comparison in C++ [duplicate]](http://stackoverflow.com/questions/23943728/case-insensitive-standard-string-comparison-in-c)
// [Remove spaces from std::string in C++](http://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c)
// [What's the best way to trim std::string?](http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
// https://github.com/nu774/qaac/blob/master/strutil.h
// [How to convert wstring into string?](https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string)
// [Find if string ends with another string in C++](https://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c)
// [Convert a String In C++ To Upper Case](https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case)
// [trim for both std::string and std::wstring](https://stackoverflow.com/questions/63808539/trim-for-both-stdstring-and-stdwstring)
// [Trim whitespace from a String](https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string)
// https://github.com/microsoft/PowerToys/blob/master/src/common/string_utils.h
// https://github.com/imageworks/pystring/blob/master/pystring.h
// https://github.com/Blinue/Magpie/blob/main/Runtime/StrUtils.h
// https://github.com/open-license-manager/licensecc/blob/develop/src/library/base/string_utils.h
// https://github.com/abseil/abseil-cpp/blob/master/absl/strings/strip.h
// https://github.com/abseil/abseil-cpp/blob/master/absl/strings/str_cat.h
// https://github.com/abseil/abseil-cpp/blob/master/absl/strings/substitute.h
// https://github.com/abseil/abseil-cpp/blob/master/absl/strings/str_replace.h
