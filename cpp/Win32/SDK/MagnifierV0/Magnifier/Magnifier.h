#pragma once

#include <memory>

#include "MagOptions.h"

#define MAGNIFIER_WNDCLASS _T("MagnifierByMYD")

namespace Gdiplus { class Graphics; }

namespace Mag
{

class Focus;
class Region;
namespace Utility { class Canvas; }

class Magnifier
{
public:
    Magnifier();
    ~Magnifier();

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
    void OnPaint(HWND hwnd);
    UINT OnNCHitTest(HWND hwnd, int x, int y);
    void OnSize(HWND hwnd, UINT state, int cx, int cy);
    void OnTimer(HWND hwnd, UINT id);

    LPCTSTR GetTitle() const { return m_Options.szTitle; }
    LPCTSTR GetClass() const { return MAGNIFIER_WNDCLASS; }

private:
    Options m_Options;
    std::unique_ptr<Region> m_Region;
    std::unique_ptr<Focus> m_Focus;

    SIZE m_szClient;
    std::unique_ptr<Utility::Canvas> m_Canvas;
    std::unique_ptr<Gdiplus::Graphics> m_Graphics;
};

} // -- namespace Mag