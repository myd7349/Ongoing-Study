#pragma once

#include <cassert>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>

#include "StringUtility.h"


template <typename T, typename CharT = wchar_t>
struct ConfigItemConverter
{
    typedef const CharT *StringT;

    T FromString(StringT s, bool &ok, T defaultValue = T()) const;
    std::basic_string<CharT> ToString(T value) const;
};


template <>
inline int ConfigItemConverter<int, wchar_t>::FromString(StringT s, bool &ok, int defaultValue) const
{
    if (s == nullptr)
    {
        ok = false;
        return defaultValue;
    }

    wchar_t *endptr;
    long value = std::wcstol(s, &endptr, 0);
    if (errno == ERANGE || *endptr != L'\0' || s == endptr)
    {
        ok = false;
        return defaultValue;
    }

#if LONG_MIN < INT_MIN || LONG_MAX > INT_MAX
    if (value < INT_MIN || value > INT_MAX)
    {
        errno = ERANGE;
        ok = false;
        return defaultValue;
    }
#endif

    ok = true;
    return static_cast<int>(value);
}


template <>
inline std::wstring ConfigItemConverter<int, wchar_t>::ToString(int value) const
{
    return std::to_wstring(static_cast<long long>(value));
}


template <>
inline double ConfigItemConverter<double, wchar_t>::FromString(StringT s, bool &ok, double defaultValue) const
{
    if (s == nullptr)
    {
        ok = false;
        return defaultValue;
    }

    wchar_t *endptr;
    double value = std::wcstod(s, &endptr); 
    if (errno == ERANGE || *endptr != L'\0' || s == endptr)
    {
        ok = false;
        return defaultValue;
    }

    ok = true;
    return value;
}


template <>
inline std::wstring ConfigItemConverter<double, wchar_t>::ToString(double value) const
{
    return std::to_wstring(static_cast<long double>(value));
}


template <>
inline std::wstring ConfigItemConverter<std::wstring, wchar_t>::FromString(StringT s, bool &ok, std::wstring defaultValue) const
{
    if (s == nullptr)
    {
        ok = false;
        return defaultValue;
    }

    ok = true;
    return s;
}


template <>
inline std::wstring ConfigItemConverter<std::wstring, wchar_t>::ToString(std::wstring value) const
{
    return value;
}


template <>
inline bool ConfigItemConverter<bool, wchar_t>::FromString(StringT s, bool &ok, bool defaultValue) const
{
    if (s == nullptr)
    {
        ok = false;
        return defaultValue;
    }

    std::wstring value(s);
    Trim(value);
    ToLower(value);

    if (value.empty())
    {
        ok = true;
        return defaultValue;
    }
    else if (value == L"1" || value == L"true" || value == L"on" || value == L"yes")
    {
        ok = true;
        return true;
    }
    else if (value == L"0" || value == L"false" || value == L"off" || value == L"no")
    {
        ok = true;
        return false;
    }
    else
    {
        ok = false;
        return defaultValue;
    }
}


#ifndef TRUE_STRING_LITERAL
# define TRUE_STRING_LITERAL "true"
#endif


#ifndef FALSE_STRING_LITERAL
# define FALSE_STRING_LITERAL "false"
#endif


#define WIDEN_IMPL(x) L ## x
#define WIDEN(x) WIDEN_IMPL(x)


template <>
inline std::wstring ConfigItemConverter<bool, wchar_t>::ToString(bool value) const
{
    return value ? WIDEN(TRUE_STRING_LITERAL) : WIDEN(FALSE_STRING_LITERAL);
}


// References:
// https://stackoverflow.com/questions/22865622/atoi-vs-atol-vs-strtol-vs-strtoul-vs-sscanf
// https://stackoverflow.com/questions/4308536/converting-a-string-into-a-double
// https://www.zhihu.com/question/27873786/answer/38454577
// https://github.com/boostorg/program_options/blob/develop/src/value_semantic.cpp#L140-L162
