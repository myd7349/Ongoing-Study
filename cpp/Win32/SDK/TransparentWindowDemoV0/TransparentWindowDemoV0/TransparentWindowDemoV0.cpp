#include "TransparentWindowDemoV0.h"

#include "framework.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                      // current instance
WCHAR szTitle[MAX_LOADSTRING];        // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];  // the main window class name
HFONT hFont;
TIME_ZONE_INFORMATION tzi;

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void Cls_OnPaint(HWND hwnd);
BOOL Cls_OnEraseBkgnd(HWND hwnd, HDC hdc);
UINT Cls_OnNCHitTest(HWND hwnd, int x, int y);
void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);
void Cls_OnTimer(HWND hwnd, UINT id);
void Cls_OnDestroy(HWND hwnd);

const UINT_PTR TIMER_ID = 0x1001;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: Place code here.

  // Initialize global strings
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_TRANSPARENTWINDOWDEMOV0, szWindowClass,
              MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance(hInstance, nCmdShow)) {
    return FALSE;
  }

  HACCEL hAccelTable =
      LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRANSPARENTWINDOWDEMOV0));

  MSG msg;

  // Main message loop:
  while (GetMessage(&msg, nullptr, 0, 0)) {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon =
      LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRANSPARENTWINDOWDEMOV0));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  // MAKEINTRESOURCEW(IDC_TRANSPARENTWINDOWDEMOV0);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  hInst = hInstance;  // Store instance handle in our global variable

  HWND hWnd =
      CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                    0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd) {
    return FALSE;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
  switch (message) {
    HANDLE_MSG(hWnd, WM_CREATE, Cls_OnCreate);
    HANDLE_MSG(hWnd, WM_COMMAND, Cls_OnCommand);
    HANDLE_MSG(hWnd, WM_PAINT, Cls_OnPaint);
    HANDLE_MSG(hWnd, WM_ERASEBKGND, Cls_OnEraseBkgnd);
    HANDLE_MSG(hWnd, WM_NCHITTEST, Cls_OnNCHitTest);
    HANDLE_MSG(hWnd, WM_SIZE, Cls_OnSize);
    HANDLE_MSG(hWnd, WM_TIMER, Cls_OnTimer);
    HANDLE_MSG(hWnd, WM_DESTROY, Cls_OnDestroy);
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);
  switch (message) {
    case WM_INITDIALOG:
      return (INT_PTR)TRUE;

    case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
      }
      break;
  }
  return (INT_PTR)FALSE;
}

BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
  SetWindowLong(hwnd, GWL_EXSTYLE,
                GetWindowLong(hwnd, GWL_EXSTYLE) ^ WS_EX_LAYERED);
  SetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 0, LWA_COLORKEY);

  GetTimeZoneInformation(&tzi);

  LOGFONT lf;
  memset(&lf, 0, sizeof(LOGFONT));
  lf.lfHeight = 50;  // request a 12-pixel-height font
  _tcsncpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial"), 7);
  hFont = CreateFontIndirect(&lf);

  SetTimer(hwnd, TIMER_ID, 800, NULL);
  return TRUE;
}

void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
  switch (id) {
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

void Render(HWND hwnd, HDC hdc) {
  // int oldBkMode = SetBkMode(hdc, TRANSPARENT);
  HFONT hOldFont = SelectFont(hdc, hFont);

  RECT clientRect;
  GetClientRect(hwnd, &clientRect);

  SYSTEMTIME st;
  GetSystemTime(&st);
  SystemTimeToTzSpecificLocalTime(&tzi, &st, &st);

  TCHAR szBuffer[1024];
  StringCchPrintf(szBuffer, ARRAYSIZE(szBuffer),
                  TEXT("Hello, world!\n%02d:%02d:%02d"), st.wHour, st.wMinute,
                  st.wSecond);

  size_t length;
  if (SUCCEEDED(StringCchLength(szBuffer, ARRAYSIZE(szBuffer), &length)))
    DrawTextW(hdc, szBuffer, length, &clientRect, DT_CENTER | DT_VCENTER);

  SelectFont(hdc, hFont);
  // SetBkMode(hdc, oldBkMode);
}

void Cls_OnPaint(HWND hwnd) {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hwnd, &ps);

  Render(hwnd, hdc);

  EndPaint(hwnd, &ps);
}

BOOL Cls_OnEraseBkgnd(HWND hwnd, HDC hdc) { return TRUE; }

UINT Cls_OnNCHitTest(HWND hwnd, int x, int y) { return HTCAPTION; }

void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy) {}

void Cls_OnTimer(HWND hwnd, UINT id) {
  if (TIMER_ID == id) {
    HDC hdc = GetDC(hwnd);
    Render(hwnd, hdc);
    ReleaseDC(hwnd, hdc);
  }
}

void Cls_OnDestroy(HWND hwnd) {
  KillTimer(hwnd, TIMER_ID);
  if (hFont != nullptr) DeleteFont(hFont);
  PostQuitMessage(0);
}

// clang-format off
// References:
// [Transparent, Click-Through Forms](https://www.codeproject.com/Articles/12877/Transparent-Click-Through-Forms)
// [Transparent hwnd window](https://stackoverflow.com/questions/23585212/transparent-hwnd-window)
// [Transparent win32 window and text](https://stackoverflow.com/questions/15605655/transparent-win32-window-and-text)
// [how to create transparent dialog ( not invisible) but image or text drawn on it is visible in MFC?](https://stackoverflow.com/questions/17251692/how-to-create-transparent-dialog-not-invisible-but-image-or-text-drawn-on-it)
// [UpdateLayeredWindow and DrawText](https://stackoverflow.com/questions/5309914/updatelayeredwindow-and-drawtext)
// [Creating a transparent window in C++ Win32](https://stackoverflow.com/questions/3970066/creating-a-transparent-window-in-c-win32)
// [Win32 transparent controls on all versions ofWindows](https://stackoverflow.com/questions/4430559/win32-transparent-controls-on-all-versions-ofwindows/4448080#4448080)
// [Creating a text label with a transparent background using WinAPI](https://stackoverflow.com/questions/7245169/creating-a-text-label-with-a-transparent-background-using-winapi)
// [Windows: Transparent window with opaque contents (LWA_COLORKEY)?](https://forum.unity.com/threads/solved-windows-transparent-window-with-opaque-contents-lwa_colorkey.323057/)
// [C++ GDI+ drawing text on a transparent layered window](https://stackoverflow.com/questions/4783781/c-gdi-drawing-text-on-a-transparent-layered-window)
// [How to draw text with transparency using GDI?](https://stackoverflow.com/questions/42221322/how-to-draw-text-with-transparency-using-gdi)
// https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/015b61a7-8fb3-48ef-be16-17366fcd67ab/c-how-to-create-and-display-a-transparent-icon-on-windows-frame-border
// https://www.gamedev.net/forums/topic/454940-win32-apic-text-on-transparent-backgound/
// clang-format on
