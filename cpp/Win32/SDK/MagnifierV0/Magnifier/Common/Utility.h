// 2015-11-20T09:10+08:00
#pragma once

#include <cassert>

#include <WinDef.h>

#include "Validate.h"

#ifndef ASSERT
# define ASSERT(expr) assert(expr)
#endif

#ifndef ASSERT_VALID
# define ASSERT_VALID(v) ASSERT(Mag::Utility::Validate(v))
#endif

#ifndef VERIFY
# ifdef NDEBUG
#  define VERIFY(expr) ((void)(expr))
# else
#  define VERIFY(expr) ASSERT(expr)
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

inline SIZE RECTToSIZE(const RECT &rc)
{
    SIZE size = { RCWidth(rc), RCHeight(rc) };
    return size;
}

inline RECT SIZEToRECT(const SIZE &size)
{
    RECT rc = { 0, 0, size.cx, size.cy };
    return rc;
}

} // namespace Utility
} // namespace Mag