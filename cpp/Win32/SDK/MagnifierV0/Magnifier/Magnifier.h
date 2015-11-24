#pragma once

#include <memory>

#include "MagFocus.h"
#include "MagOptions.h"

#define MAGNIFIER_WNDCLASS _T("MagnifierByMYD")

namespace Mag
{
class MagInstance;

class Magnifier
{
public:
    Magnifier();
    ~Magnifier();

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
    void OnPaint(HWND hwnd);
    void OnDestroy(HWND hwnd);

    LPCTSTR GetTitle() const { return m_Options.szTitle; }
    LPCTSTR GetClass() const { return MAGNIFIER_WNDCLASS; }

private:
    Options m_Options;
    std::unique_ptr<MagInstance> m_Mag;
    std::unique_ptr<Focus> m_Focus;
};
} // -- namespace Mag