#pragma once

#include <memory>

#include <WinUser.h>

#include "MagOptions.h"
#include "Common/GdiplusHelper.h"

#define MAGNIFIER_WNDCLASS _T("MagnifierByMYD")

// void Cls_OnMagnify(HWND hwnd);
#define UM_MAGNIFY (WM_APP + WM_PAINT)
#define HANDLE_UM_MAGNIFY(hwnd, wParam, lParam, fn) \
    ((fn)(hwnd), 0L)
#define FORWARD_UM_MAGNIFY(hwnd, fn) \
    (void)(fn)((hwnd), UM_MAGNIFY, 0L, 0L)

namespace Gdiplus { class Graphics; }

namespace Mag
{

class Focus;
class Region;
namespace Utility { class Canvas; }

class Magnifier : private Utility::GdiplusConsumer
{
public:
    Magnifier();
    ~Magnifier();

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
    void OnPaint(HWND hwnd);
    UINT OnNCHitTest(HWND hwnd, int x, int y);
    void OnSize(HWND hwnd, UINT state, int cx, int cy);
    void OnTimer(HWND hwnd, UINT id);
    void OnMagnify(HWND hwnd);

    LPCTSTR GetTitle() const { return m_Options.szTitle; }
    LPCTSTR GetClass() const { return MAGNIFIER_WNDCLASS; }

private:
    void CalcMagParam(RECT &rcMagWnd, RECT &rcMagArea, POINT &ptFocus, HWND hwnd);
    void Update(HWND hwnd, HDC hdc);

private:
    Options m_Options;
    std::unique_ptr<Region> m_Region;
    std::unique_ptr<Focus> m_Focus;

    SIZE m_szClient;
    std::unique_ptr<Utility::Canvas> m_Canvas;
    std::unique_ptr<Gdiplus::Graphics> m_Graphics;
};

} // -- namespace Mag