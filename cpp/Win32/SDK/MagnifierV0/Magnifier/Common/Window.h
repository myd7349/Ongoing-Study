// 2015-12-03T09:26+08:00
#pragma once

#include <WinDef.h>

#include "Property.h"

namespace Mag
{
namespace Utility
{

class Window
{
public:
    Window();
    virtual ~Window();

    BOOL Create(DWORD dwExStyle, LPCTSTR lpClass, LPCTSTR lpTitle, 
        DWORD dwStyle, int x, int y, int nWidth, int nHeight, 
        HWND hWndParent, HMENU hMenu, HINSTANCE hInst, LPVOID lpParam);

    RW_PROPERTY(int, X)
    RW_PROPERTY(int, Y)
    RW_PROPERTY(int, Width)
    RW_PROPERTY(int, Height)
    RW_PROPERTY(DWORD, Style)
    RW_PROPERTY(DWORD, ExStyle)
    RW_PROPERTY(LPCTSTR, Title)
    RO_PROPERTY(LPCTSTR, Class)
    RO_PROPERTY(HWND, HWnd)

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL &bProcessed);

private:
    struct WindowClass : public WNDCLASSEX
    {
        WindowClass();
        ~WindowClass();

        ATOM Register();
        void UnRegister();
    };

    static LRESULT CALLBACK BaseWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    WNDCLASSEX m_wcex;
    CREATESTRUCT m_cs;
    HINSTANCE m_hInst;
    HWND m_hWnd;
    BOOL m_bProcessed;

    static const UINT MAX_SIZE = 128;
    TCHAR szClass[MAX_SIZE];
    TCHAR szTitle[MAX_SIZE];
};

} // namespace Utility
} // namespace Mag

// References:
//