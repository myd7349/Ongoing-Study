// 2015-11-11T09:32+08:00
#pragma once

#include <WinDef.h>

namespace Mag
{
enum MAG_STYLE
{
    MAGS_STATIC,
    MAGS_TRACKCUR,
    MAGS_DRAGABLE,
};

enum MAG_MODE
{
    MAGM_DYNAMIC,
    MAGM_SNAPSHOT,
};

enum MAG_FOCUS
{
    MAGF_CROSS,
    MAGF_X,
    MAGF_RECT,
};

struct Options
{
    DWORD dwExStyle;
    DWORD dwStyle;
    MAG_STYLE style;
    MAG_MODE mode;
    COLORREF clrFocus;
    COLORREF clrBkgnd;
    COLORREF clrText;
    COLORREF clrReserved;
    BOOL bAutoHide;
    BOOL bShowFocus;
    BOOL bShowFactor;
    BOOL bShowPos;
    BOOL bInvertColor;
    BOOL bIsClientSize;
    int nWidth;
    int nHeight;
    MAG_FOCUS focus;
    int nFocusHalfLen;
    double dFactor;
    double dFactorMin;
    double dFactorMax;
    TCHAR szTitle[96];

    static void Reset(Options &options);
    static BOOL Load(Options &options);
    static void LoadEx(Options &options);
    static BOOL Save(const Options &options);
};

} // namespace Mag
