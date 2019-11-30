#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif  // WIN32_LEAN_AND_MEAN

#include <windows.h>

HBITMAP ReadPixelsToHBITMAP(HDC hdc, int x, int y, int width, int height,
                            BOOL bUseBackBuffer);
