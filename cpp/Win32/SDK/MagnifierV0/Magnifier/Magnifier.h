#pragma once

#include <memory>

#include "MagOptions.h"

#define MAGNIFIER_WNDCLASS _T("MagnifierByMYD")

namespace Mag
{
class MagInstance;
class Focus;
namespace Utility { class Canvas; }

class Magnifier
{
public:
    Magnifier();
    ~Magnifier();

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
    void OnPaint(HWND hwnd);
    void OnSize(HWND hwnd, UINT state, int cx, int cy);
    void OnDestroy(HWND hwnd);

    LPCTSTR GetTitle() const { return m_Options.szTitle; }
    LPCTSTR GetClass() const { return MAGNIFIER_WNDCLASS; }

private:
    Options m_Options;
    std::unique_ptr<MagInstance> m_Mag;
    std::unique_ptr<Focus> m_Focus;

private:
    std::unique_ptr<Utility::Canvas> m_Canvas;
    SIZE m_szClient;
};
} // -- namespace Mag