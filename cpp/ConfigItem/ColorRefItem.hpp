#pragma once

#include <Windows.h>

#include "ConfigItem.hpp"


struct ColorRef
{
    ColorRef(COLORREF color = RGB(0, 0, 0))
        : Color(color)
    {
    }

    operator COLORREF() const
    {
        return Color;
    }

    COLORREF Color;
};

inline bool operator==(const ColorRef &lhs, const ColorRef &rhs)
{
    return lhs.Color == rhs.Color;
}

inline bool operator!=(const ColorRef &lhs, const ColorRef &rhs)
{
    return !operator==(lhs, rhs);
}

typedef ConfigItem<ColorRef> ColorRefItem;
