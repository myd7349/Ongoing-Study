// 2015-12-02T09:56+08:00
#pragma once

#include "Common.h"

namespace Mag
{
namespace Utility
{

template <typename T>
inline BOOL Validate(T t)
{
    return TRUE;
}

template <>
inline BOOL Validate(HDC hdc)
{
    return hdc != NULL;
}

template <>
inline BOOL Validate(HWND hwnd)
{
    return hwnd != NULL && IsWindow(hwnd);
}

} // namespace Utility
} // namespace Mag
