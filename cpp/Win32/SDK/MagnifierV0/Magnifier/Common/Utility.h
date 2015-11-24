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

} // namespace Utility
} // namespace Mag