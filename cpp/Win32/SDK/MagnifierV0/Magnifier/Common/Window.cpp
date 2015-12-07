#include "Common.h"
#include "Window.h"
#include "Utility.h"

namespace Mag
{
namespace Utility
{

Window::WindowClass::WindowClass()
{

}

Window::WindowClass::~WindowClass()
{
}

ATOM Window::WindowClass::Register()
{
    return 0;
}

void Window::WindowClass::UnRegister()
{
}

Window::Window()
{
    m_wcex.cbSize        = sizeof(WNDCLASSEX);

    m_wcex.style         = CS_HREDRAW | CS_VREDRAW;
    m_wcex.lpfnWndProc   = BaseWndProc;
    m_wcex.cbClsExtra    = 0;
    m_wcex.cbWndExtra    = 0;
    m_wcex.hInstance     = NULL;
    m_wcex.hIcon         = NULL;
    m_wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    m_wcex.lpszMenuName	 = NULL;
    m_wcex.lpszClassName = NULL;
    m_wcex.hIconSm		 = NULL;
}

Window::~Window()
{
}

BOOL Window::Create(DWORD dwExStyle, LPCTSTR lpClass, LPCTSTR lpTitle, 
    DWORD dwStyle,int x, int y, int nWidth, int nHeight, HWND hWndParent, 
    HMENU hMenu, HINSTANCE hInst, LPVOID lpParam)
{
    m_cs.lpCreateParams = lpParam;
    m_cs.hInstance = hInst;
    m_cs.hMenu = hMenu;
    m_cs.hwndParent = hWndParent;
    m_cs.cx = nWidth;
    m_cs.cy = nHeight;
    m_cs.x = x;
    m_cs.y = y;
    m_cs.style = dwStyle;
    m_cs.lpszName = NULL;
    m_cs.lpszClass = NULL;
    m_cs.dwExStyle = dwExStyle;

    if (!PreCreateWindow(m_cs))
    {
        return FALSE;
    }

    return TRUE;
}

LRESULT CALLBACK Window::BaseWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

BOOL Window::PreCreateWindow(CREATESTRUCT &cs)
{
    return TRUE;
}

LRESULT Window::WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL &bProcessed)
{
    return 0;
}

PROPERTY_GETTER(Window, int, X) { return m_cs.x; }
PROPERTY_GETTER(Window, int, Y) { return m_cs.y; }
PROPERTY_GETTER(Window, int, Width) { return m_cs.cx; }
PROPERTY_GETTER(Window, int, Height) { return m_cs.cy; }
PROPERTY_GETTER(Window, DWORD, Style) { return m_cs.style; }
PROPERTY_GETTER(Window, DWORD, ExStyle) { return m_cs.dwExStyle; }
PROPERTY_GETTER(Window, LPCTSTR, Title) { return m_cs.lpszName; }
PROPERTY_GETTER(Window, LPCTSTR, Class) { return m_cs.lpszClass; }
PROPERTY_GETTER(Window, HWND, HWnd) { ASSERT_VALID(m_hWnd); return m_hWnd; }

PROPERTY_SETTER(Window, int, X, x)
{
    m_cs.x = x;
    // TODO
}

PROPERTY_SETTER(Window, int, Y, y)
{
    m_cs.y = y;
    // TODO
}

PROPERTY_SETTER(Window, int, Width, nWidth)
{
    m_cs.cx = nWidth;
    // TODO
}

PROPERTY_SETTER(Window, int, Height, nHeight)
{
    m_cs.cy = nHeight;
    // TODO
}

PROPERTY_SETTER(Window, DWORD, Style, dwStyle)
{
    m_cs.style = dwStyle;
    // TODO
}

PROPERTY_SETTER(Window, DWORD, ExStyle, dwExStyle)
{
    m_cs.dwExStyle = dwExStyle;
    // TODO
}

PROPERTY_SETTER(Window, LPCTSTR, Title, lpcszTitle)
{
    // TODO
}

} // namespace Utility
} // namespace Mag