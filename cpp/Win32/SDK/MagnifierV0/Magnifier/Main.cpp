// 2015-11-11T09:23+08:00
#include "stdafx.h"
#include "Magnifier.h"
#include "MagOptionsDlg.h"
#include "resource.h"


ATOM MyRegisterClass(HINSTANCE, LPCTSTR);
HWND InitInstance(HINSTANCE, LPCTSTR, LPCTSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Cls_OnPaint(HWND hwnd);
UINT Cls_OnNCHitTest(HWND hwnd, int x, int y);
void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);
void Cls_OnTimer(HWND hwnd, UINT id);
void Cls_OnMagnify(HWND hwnd);
void Cls_OnDestroy(HWND hwnd);

const UINT_PTR TIMER_ID = 0x1001;

namespace
{
HINSTANCE hInst;
Mag::Magnifier g_Mag;
}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    HACCEL hAccelTable;

    HWND hWnd = NULL;
    BOOL bRet;

    MyRegisterClass(hInstance, MAGNIFIER_WNDCLASS);

    if ((hWnd = InitInstance(hInstance, g_Mag.GetClass(), g_Mag.GetTitle(), nCmdShow)) == NULL)
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAGNIFIER));

#if 0
    UNREFERENCED_PARAMETER(bRet);

    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Cls_OnMagnify(hWnd);
            Sleep(16);
        }
    }
#else
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (-1 == bRet)
        {
            break;
        }
        else if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
#endif

    return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR lpcszWindowClass)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAGNIFIER));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL; //MAKEINTRESOURCE(IDC_MAGNIFIER);
    wcex.lpszClassName = lpcszWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}


HWND InitInstance(HINSTANCE hInstance, LPCTSTR lpcszWindowClass, LPCTSTR lpcszTitle, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance;

    hWnd = CreateWindowEx(WS_EX_STATICEDGE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW, lpcszWindowClass, lpcszTitle,
        WS_POPUP | WS_CAPTION | WS_SYSMENU, 0, 0, 200, 200, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return NULL;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    HANDLE_MSG(hWnd, WM_CREATE, Cls_OnCreate);
    HANDLE_MSG(hWnd, WM_COMMAND, Cls_OnCommand);
    HANDLE_MSG(hWnd, WM_PAINT, Cls_OnPaint);
    HANDLE_MSG(hWnd, WM_NCHITTEST, Cls_OnNCHitTest);
    HANDLE_MSG(hWnd, WM_SIZE, Cls_OnSize);
    HANDLE_MSG(hWnd, WM_TIMER, Cls_OnTimer);
    HANDLE_MSG(hWnd, UM_MAGNIFY, Cls_OnMagnify);
    HANDLE_MSG(hWnd, WM_DESTROY, Cls_OnDestroy);
    default:
	    return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}


BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    SetTimer(hwnd, TIMER_ID, 16, NULL);
    return g_Mag.OnCreate(hwnd, lpCreateStruct);
}


void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDM_HELP_OPTIONS:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_OPTIONS), hwnd, OptionsDlgProc);
        break;
    case IDM_EXIT:
        DestroyWindow(hwnd);
        break;
    default:
        FORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, DefWindowProc);
    }
}


void Cls_OnPaint(HWND hwnd)
{
    g_Mag.OnPaint(hwnd);
}


UINT Cls_OnNCHitTest(HWND hwnd, int x, int y)
{
    return g_Mag.OnNCHitTest(hwnd, x, y);
}


void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    g_Mag.OnSize(hwnd, state, cx, cy);
}


void Cls_OnTimer(HWND hwnd, UINT id)
{
    if (TIMER_ID == id)
    {
        g_Mag.OnTimer(hwnd, id);
    }
}


void Cls_OnMagnify(HWND hwnd)
{
    g_Mag.OnMagnify(hwnd);
}


void Cls_OnDestroy(HWND hwnd)
{
    KillTimer(hwnd, TIMER_ID);
    PostQuitMessage(0);
}
