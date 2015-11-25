// 2015-11-25T13:20+08:00
#pragma once

#include "Common.h"
#include "Noncopyable.h"

#include <cassert>

namespace Mag
{
namespace Utility
{

class Canvas : private Noncopyable
{
public:
    Canvas(HDC hdc, int cx, int cy);
    virtual ~Canvas();

    HDC &GetHDC() { assert(m_hMemDC != NULL); return m_hMemDC; }
    HBITMAP &GetHBITMAP() { assert(m_hBmpCanvas != NULL); return m_hBmpCanvas; }

private:
    HDC m_hMemDC;
    HBITMAP m_hBmpCanvas;
    HBITMAP m_hBmpOld;
};

} // namespace Utility
} // namespace Mag