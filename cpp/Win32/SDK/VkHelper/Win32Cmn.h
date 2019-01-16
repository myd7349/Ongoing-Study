// 2016-11-26T15:11+08:00
#ifndef WIN32CMN_H_
#define WIN32CMN_H_

#include "targetver.h"

#define STRICT (1)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>

#include <cassert>

#define Assert(expr, msg) assert(((void)msg, expr))

#ifdef NDEBUG
# define Verify(exp) (exp)
#else
# define Verify(exp) assert(exp)
#endif

#endif // WIN32CMN_H_
