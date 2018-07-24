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


#define DEFINE_CONVERTER(T, CharT, FromStringFunc, ToStringFunc) \
template <> \
inline T ConfigItemConverter<T, CharT>::FromString(StringT s, bool &ok, T defaultValue) const \
{ \
    T value = FromStringFunc(s, ok); \
    if (!ok) \
        return defaultValue; \
    \
    return value; \
} \
\
template <> \
inline std::basic_string<CharT> ConfigItemConverter<T, CharT>::ToString(T value) const \
{ \
    return ToStringFunc(value); \
}


inline int WStringToInt(const wchar_t *s, bool &ok)
{
    if (s == nullptr)
    {
        ok = false;
        return 0;
    }

    int value = _wtoi(s);
    if (errno == ERANGE || errno == EINVAL)
    {
        ok = false;
        return 0;
    }

    ok = true;
    return value;
}


template <typename TTarget, typename TSource>
inline std::wstring IntegerToWString(TSource value)
{
    return std::to_wstring(static_cast<TTarget>(value));
}


inline std::wstring WStringToWString(const wchar_t *s, bool &ok)
{
    if (s == nullptr)
    {
        ok = false;
        return L"";
    }

    ok = true;
    return std::wstring(s);
}


DEFINE_CONVERTER(int, wchar_t, WStringToInt, IntegerToWString<long long>)
DEFINE_CONVERTER(std::wstring, wchar_t, WStringToWString, )
