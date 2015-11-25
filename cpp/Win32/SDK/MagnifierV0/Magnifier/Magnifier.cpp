#include "stdafx.h"
#include "MagDynamic.h"
#include "MagFocus.h"
#include "Magnifier.h"
#include "MagSnapshot.h"
#include "Common/Canvas.h"
#include "Common/Utility.h"


#define MAX_FACTOR (5.0)
#define MIN_FACTOR (0.5)
#define DYNAMIC_MODE (TRUE)


namespace
{
void CalcMagParam(RECT &rcMagWnd, RECT &rcMagArea, POINT &ptFocus, HWND hwnd, const POINT &ptCur, int width, int height, double factor);
} // namespace -


namespace Mag
{
Magnifier::Magnifier()
{
    Options::LoadEx(m_Options);
}


Magnifier::~Magnifier()
{
}


BOOL Magnifier::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    assert(IsWindow(hwnd));
    UNREFERENCED_PARAMETER(lpCreateStruct);

    SetWindowLongPtr(hwnd, GWL_STYLE, m_Options.dwStyle);
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, m_Options.dwExStyle);

    if (m_Options.bIsClientSize)
    {
        Utility::SetClientSize(hwnd, m_Options.nWidth, m_Options.nHeight);
    }
    else
    {
        SetWindowPos(hwnd, HWND_TOPMOST, 
            0, 0, m_Options.nWidth, m_Options.nHeight, 
            SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
    }

    switch (m_Options.mode)
    {
    case MAGM_DYNAMIC: m_Mag.reset(new MagDynamic); break;
    case MAGM_SNAPSHOT: m_Mag.reset(new MagSnapshot); break;
    default: assert(FALSE); break;
    }

    switch (m_Options.focus)
    {
    case MAGF_CROSS:
        m_Focus.reset(new FocusCross(m_Options.nFocusHalfLen, m_Options.clrFocus));
        break;
    case MAGF_X:
        m_Focus.reset(new FocusX(m_Options.nFocusHalfLen, m_Options.clrFocus));
        break;
    case MAGF_RECT:
        m_Focus.reset(new FocusRect(m_Options.nFocusHalfLen, m_Options.clrFocus));
        break;
    default: assert(FALSE); break;
    }

    return TRUE;
}


void Magnifier::OnPaint(HWND hwnd)
{
    assert(IsWindow(hwnd));
    assert(m_Canvas != nullptr);

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    POINT pt;
    GetCursorPos(&pt);

    RECT rcMagWnd;
    RECT rcMagArea;
    POINT ptFocus;

    CalcMagParam(rcMagWnd, rcMagArea, ptFocus, hwnd, pt, 
        m_szClient.cx, m_szClient.cy, m_Options.dFactor);
    SetWindowPos(hwnd, HWND_TOPMOST, 
        rcMagWnd.left, rcMagWnd.top, rcMagWnd.right - rcMagWnd.left, rcMagWnd.bottom - rcMagWnd.top, 
        SWP_NOACTIVATE | SWP_NOSIZE);
    
    m_Mag->Draw(m_Canvas->GetHDC(), Utility::SIZEToRECT(m_szClient), rcMagArea);

    Gdiplus::Graphics canvas(m_Canvas->GetHDC());
    m_Focus->Draw(canvas, Utility::POINTToPointF(ptFocus));

    BitBlt(hdc, 0, 0, m_szClient.cx, m_szClient.cy, m_Canvas->GetHDC(), 0, 0, SRCCOPY);

    EndPaint(hwnd, &ps);
}


void Magnifier::OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    m_szClient.cx = cx;
    m_szClient.cy = cy;

    if (cx > 0 && cy > 0)
    {
        HDC hdc = GetDC(hwnd);
        m_Canvas.reset(new Utility::Canvas(hdc, cx, cy));
        ReleaseDC(hwnd, hdc);
    }
}


void Magnifier::OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}
} // namespace Mag


namespace
{
void AdjustFactor(double &factor)
{
    if (factor < MIN_FACTOR)
    {
        factor = MIN_FACTOR;
    }
    else if (factor > MAX_FACTOR)
    {
        factor = MAX_FACTOR;
    }
}


void CalcMagAreaRect(RECT &rcMag, POINT &ptFocus, const POINT &ptCur, int width, int height, double factor)
{
    int w = (int)(width / factor);
    int h = (int)(height / factor);

    rcMag.left = ptCur.x - w / 2;
    rcMag.top = ptCur.y - h / 2;

    if (rcMag.left < 0)
    {
        rcMag.left = 0;
    }
    else if (rcMag.left > GetSystemMetrics(SM_CXSCREEN) - w)
    {
        rcMag.left = GetSystemMetrics(SM_CXSCREEN) - w;
    }
    rcMag.right = rcMag.left + w;

    if (rcMag.top < 0)
    {
        rcMag.top = 0;
    }
    else if (rcMag.top > GetSystemMetrics(SM_CYSCREEN) - h)
    {
        rcMag.top = GetSystemMetrics(SM_CYSCREEN) - h;
    }
    rcMag.bottom = rcMag.top + h;

    ptFocus.x = (LONG)((ptCur.x - rcMag.left) * factor);
    ptFocus.y = (LONG)((ptCur.y - rcMag.top) * factor);
}


enum ERelCorner
{
    ERC_LT,     // Left-Top Corner
    ERC_RT,     // Right-Top Corner
    ERC_CENTER, // Center
    ERC_LB,     // Left-Bottom Corner
    ERC_RB,     // Right-Bottom Corner
};


void CalcMagWndRect(HWND hwnd, RECT &rcMag, const POINT &ptCur,
    int cxOffset, int cyOffset, ERelCorner corner, int width, int height)
{
    int cxScreen = GetSystemMetrics(SM_CXSCREEN);
    int cyScreen = GetSystemMetrics(SM_CYSCREEN);

    assert(width < cxScreen && height < cyScreen);

    SetRect(&rcMag, 0, 0, width, height);

    POINT ptTopLeftCorner = {};
    POINT ptCenter = { width / 2, height / 2 };
    ClientToScreen(hwnd, &ptTopLeftCorner);
    ClientToScreen(hwnd, &ptCenter);
    int cxHalf = (int)(ptCenter.x - ptTopLeftCorner.x);
    int cyHalf = (int)(ptCenter.y - ptTopLeftCorner.y);

    switch (corner)
    {
    case ERC_LT: break;
    case ERC_RT: cxOffset -= cxHalf * 2; break;
    case ERC_CENTER: cxOffset -= cxHalf; cyOffset -= cyHalf; break;
    case ERC_LB: cyOffset -= cyHalf * 2; break;
    case ERC_RB: cxOffset -= cxHalf * 2; cyOffset -= cyHalf * 2; break;
    default: assert(FALSE); break;
    }

    OffsetRect(&rcMag, (int)ptCur.x + cxOffset, (int)ptCur.y + cyOffset);

    if (corner != ERC_CENTER)
    {
        cxOffset += cxHalf;
        cyOffset += cyHalf;
    }

    if (ptCur.x >= rcMag.left && ptCur.x <= rcMag.right)
    {
        if (rcMag.left < 0 || rcMag.right > cxScreen)
        {
            OffsetRect(&rcMag, rcMag.left < 0 ? -rcMag.left : cxScreen - rcMag.right, 0);
        }
    }
    else
    {
        if (rcMag.left < 0 || rcMag.right > cxScreen)
        {
            OffsetRect(&rcMag, -2 * cxOffset, 0);
        }
    }

    if (ptCur.y >= rcMag.top && ptCur.y <= rcMag.bottom)
    {
        if (rcMag.top < 0 || rcMag.bottom > cyScreen)
        {
            OffsetRect(&rcMag, 0, rcMag.top < 0 ? -rcMag.top : cyScreen - rcMag.bottom);
        }
    }
    else
    {
        if (rcMag.top < 0 || rcMag.bottom > cyScreen)
        {
            OffsetRect(&rcMag, 0, -2 * cyOffset);
        }
    }
}


void CalcMagParam(RECT &rcMagWnd, RECT &rcMagArea, POINT &ptFocus, 
    HWND hwnd, const POINT &ptCur, int width, int height, double factor)
{
    AdjustFactor(factor);

    CalcMagAreaRect(rcMagArea, ptFocus, ptCur, width, height, factor);

    if (DYNAMIC_MODE)
    {
        int cxOffset = (int)(max(width - ptFocus.x, ptFocus.x) / factor) + 2;
        int cyOffset = (int)(max(height - ptFocus.y, ptFocus.y) / factor) + 2;

        if (cxOffset < 16)
        {
            cxOffset = 16;
        }

        if (cyOffset < 16)
        {
            cyOffset = 16;
        }

        CalcMagWndRect(hwnd, rcMagWnd, ptCur, cxOffset, cyOffset, ERC_LT, width, height);
    }
    else
    {
        CalcMagWndRect(hwnd, rcMagWnd, ptCur, 32, 32, ERC_LT, width, height);
    }
}
} // namespace -