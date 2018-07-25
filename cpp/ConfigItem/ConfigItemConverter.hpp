#pragma once

#include <cassert>
#include <cerrno>
#include <string>
#include <cstdlib>


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

    int value = _wtoi(s);
    if (errno == ERANGE || errno == EINVAL)
    {
        ok = false;
        return defaultValue;
    }

    ok = true;
    return value;
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

    double value = wcstod(s, NULL); 
    if (errno == ERANGE)
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
