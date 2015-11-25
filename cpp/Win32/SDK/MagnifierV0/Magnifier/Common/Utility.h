// 2015-11-20T09:10+08:00
#pragma once

#include <WinDef.h>

#include <cassert>

#ifndef VERIFY
# ifdef NDEBUG
#  define VERIFY(expr) ((void)(expr))
# else
#  define VERIFY(expr) assert(expr)
# endif
#endif


namespace Mag
{
namespace Utility
{

void SetClientSize(HWND hwnd, int width, int height);

inline LONG RCWidth(const RECT &rc)
{
    return rc.right - rc.left;
}

inline LONG RCHeight(const RECT &rc)
{
    return rc.bottom - rc.top;
}

inline SIZE RCSIZE(const RECT &rc)
{
    SIZE size = { RCWidth(rc), RCHeight(rc) };
    return size;
}

} // namespace Utility
} // namespace Mag