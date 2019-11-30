#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
void CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
void EasyCreateBMPFile(LPTSTR pszFile, HBITMAP hBitmap, HDC hDC);
