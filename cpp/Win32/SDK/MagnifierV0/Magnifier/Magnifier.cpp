#include "stdafx.h"
#include "Magnifier.h"


#define CLIENT_WIDTH (400)
#define CLIENT_HEIGHT (250)
#define FACTOR (2.5)
#define MAX_FACTOR (10.0)
#define MIN_FACTOR (0.05)
#define FOCUS_COLOR RGB(0, 0, 0)
#define FOCUS_SIZE (5)
#define INVERT_COLOR (TRUE)
#define SHOW_FACTOR (TRUE)
#define SHOW_POS (TRUE)


HINSTANCE hInst;

ATOM MyRegisterClass(HINSTANCE, LPCTSTR);
HWND InitInstance(HINSTANCE, LPCTSTR, LPCTSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);


void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Cls_OnPaint(HWND hwnd);
void Cls_OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
void Cls_OnDestroy(HWND hwnd);


void SetClientSize(HWND hwnd, int width, int height);
void CalcMagParam(RECT &rcMagWnd, RECT &rcMagArea, POINT &ptFocus, HWND hwnd, const POINT &ptCur, int width, int height, double factor);


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    HACCEL hAccelTable;

    const int MAX_LOADSTRING = 64;
    TCHAR szWindowClass[MAX_LOADSTRING] = _T("");
    TCHAR szTitle[MAX_LOADSTRING] = _T("");

    HWND hWnd = NULL;

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_MAGNIFIER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, szWindowClass);

    if ((hWnd = InitInstance(hInstance, szWindowClass, szTitle, nCmdShow)) == NULL)
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAGNIFIER));

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
            InvalidateRect(hWnd, NULL, FALSE);
            Sleep(16);
        }
    }

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

    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_CLIENTEDGE, lpcszWindowClass, lpcszTitle,
        WS_POPUP, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return NULL;
    }

    SetClientSize(hWnd, CLIENT_WIDTH, CLIENT_HEIGHT);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
        HANDLE_MSG(hWnd, WM_COMMAND, Cls_OnCommand);
        HANDLE_MSG(hWnd, WM_PAINT, Cls_OnPaint);
        HANDLE_MSG(hWnd, WM_DESTROY, Cls_OnDestroy);
        default:
		    return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}

	return (INT_PTR)FALSE;
}


void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
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
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    POINT pt;
    GetCursorPos(&pt);

    RECT rcMagWnd;
    RECT rcMagArea;
    POINT ptFocus;

    CalcMagParam(rcMagWnd, rcMagArea, ptFocus, hwnd, pt, CLIENT_WIDTH, CLIENT_HEIGHT, FACTOR);
    SetWindowPos(hwnd, HWND_TOPMOST, 
        rcMagWnd.left, rcMagWnd.top, rcMagWnd.right - rcMagWnd.left, rcMagWnd.bottom - rcMagWnd.top, 
        SWP_NOACTIVATE | SWP_NOSIZE);

    {
        // GetWindowDC(GetDesktopWindow());
        // GetDC(NULL);
        HDC hdcScreen = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
        StretchBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, hdcScreen, rcMagArea.left, rcMagArea.top,
            rcMagArea.right - rcMagArea.left, rcMagArea.bottom - rcMagArea.top, SRCCOPY);
        DeleteDC(hdcScreen);

        MoveToEx(hdc, ptFocus.x - 5, ptFocus.y, NULL);
        LineTo(hdc, ptFocus.x + 5, ptFocus.y);
        MoveToEx(hdc, ptFocus.x, ptFocus.y - 5, NULL);
        LineTo(hdc, ptFocus.x, ptFocus.y + 5);
    }

    EndPaint(hwnd, &ps);
}


void Cls_OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}


void SetClientSize(HWND hwnd, int width, int height)
{
    RECT rcWindow;
    RECT rcClient;

    GetWindowRect(hwnd, &rcWindow);
    GetClientRect(hwnd, &rcClient);
    
    int cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
    int cy = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

    width += cx;
    height += cy;

    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, width, height, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


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
