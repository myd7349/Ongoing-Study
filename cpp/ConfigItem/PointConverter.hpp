#pragma once

#include <sstream>

#include "ConfigItemConverter.hpp"
#include "PointConfigItem.hpp"


template <>
inline Point ConfigItemConverter<Point, wchar_t>::FromString(StringT s, bool &ok, Point defaultValue) const
{
    std::wistringstream iss(s);
    wchar_t ch;

#define READ_CHAR_AND_VERIFY(c) \
    do \
    { \
        iss >> ch; \
        if (!iss || ch != c) \
        { \
            ok = false; \
            return defaultValue; \
        } \
    } while (0)

    READ_CHAR_AND_VERIFY(L'P');
    READ_CHAR_AND_VERIFY(L'o');
    READ_CHAR_AND_VERIFY(L'i');
    READ_CHAR_AND_VERIFY(L'n');
    READ_CHAR_AND_VERIFY(L't');
    READ_CHAR_AND_VERIFY(L'(');

    Point value;

    iss >> value.x;
    if (!iss)
    {
        ok = false;
        return defaultValue;
    }

    READ_CHAR_AND_VERIFY(L',');

    iss >> value.y;
    if (!iss)
    {
        ok = false;
        return defaultValue;
    }

    READ_CHAR_AND_VERIFY(L')');

#undef READ_CHAR_AND_VERIFY

    ok = true;
    return value;
}


template <>
inline std::wstring ConfigItemConverter<Point, wchar_t>::ToString(Point value) const
{
    std::wostringstream oss;
    oss << L"Point(" << value.x << L',' << value.y << L')';

    return oss.str();
}


// Reference:
// [C++ String stream ignore() not working](https://stackoverflow.com/questions/46480689/c-string-stream-ignore-not-working)
// [std::stringstream - discard a value](https://stackoverflow.com/questions/33561518/stdstringstream-discard-a-value)
// [How does istream::ignore( ) work?](https://stackoverflow.com/questions/14693106/how-does-istreamignore-work)
// [What is the difference between eof(), fail(), bad(), and good() in C++ streams?](https://stackoverflow.com/questions/43084612/what-is-the-difference-between-eof-fail-bad-and-good-in-c-streams)
// https://en.cppreference.com/w/cpp/io/ios_base/iostate
