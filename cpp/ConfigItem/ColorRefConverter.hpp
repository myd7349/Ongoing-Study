#pragma once

#include "ColorRefItem.hpp"
#include "ConfigItemConverter.hpp"


template <>
inline ColorRef ConfigItemConverter<ColorRef, wchar_t>::FromString(StringT s, bool &ok, ColorRef defaultValue) const
{
    int color = ConfigItemConverter<int>().FromString(s, ok, static_cast<int>(defaultValue.Color));
    if (!ok)
        return defaultValue;

    if (color < static_cast<int>(RGB(0, 0, 0)) || color > static_cast<int>(RGB(255, 255, 255)))
    {
        ok = false;
        return defaultValue;
    }

    return static_cast<COLORREF>(color);
}


template <>
inline std::wstring ConfigItemConverter<ColorRef, wchar_t>::ToString(ColorRef value) const
{
    return ConfigItemConverter<int>().ToString(static_cast<int>(value.Color));
}
