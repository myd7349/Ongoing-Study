/*
Based on Code::Blocks' OpenGL project template.
*/
#include <time.h>

#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include <gl/gl.h>

#include "../../Win32/BitmapUtility.h"
#include "../GLSnapshot.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif  // ARRAYSIZE

static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
static void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
static void DisableOpenGL(HWND, HDC, HGLRC);

static HDC g_hDC;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine, int nCmdShow) {
  WNDCLASSEX wcex;
  HWND hwnd;
  HGLRC hRC;
  MSG msg;
  BOOL bQuit = FALSE;
  float theta = 0.0f;

  /* register window class */
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_OWNDC;
  wcex.lpfnWndProc = WindowProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = _T("GLSample");
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&wcex)) return 0;

  /* create main window */
  hwnd = CreateWindowEx(0, _T("GLSample"), _T("OpenGL Sample"),
                        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640,
                        640, NULL, NULL, hInstance, NULL);

  ShowWindow(hwnd, nCmdShow);

  /* enable OpenGL for the window */
  EnableOpenGL(hwnd, &g_hDC, &hRC);

  /* program main loop */
  while (!bQuit) {
    /* check for messages */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      /* handle or dispatch messages */
      if (msg.message == WM_QUIT) {
        bQuit = TRUE;
      } else {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    } else {
      /* OpenGL animation code goes here */

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glPushMatrix();
      glRotatef(theta, 0.0f, 0.0f, 1.0f);

      glBegin(GL_TRIANGLES);

      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(0.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(0.87f, -0.5f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex2f(-0.87f, -0.5f);

      glEnd();

      glPopMatrix();

      SwapBuffers(g_hDC);

      theta += 0.1f;
      Sleep(1);
    }
  }

  /* shutdown OpenGL */
  DisableOpenGL(hwnd, g_hDC, hRC);

  /* destroy the window explicitly */
  DestroyWindow(hwnd);

  return msg.wParam;
}

static int GetCurrentDateTime(LPTSTR lpszBuffer, size_t count) {
  time_t tm;
  time(&tm);

  return _tcsftime(lpszBuffer, count, _T("%Y%m%d-%H%M%S%z"), localtime(&tm));
}

static void OnDestroy(HWND hwnd) { PostQuitMessage(0); }

static void OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {
  switch (vk) {
    case VK_ESCAPE:
      FORWARD_WM_CLOSE(hwnd, DefWindowProc);
      break;
    case VK_SPACE: {
      TCHAR szFileName[MAX_PATH];
      TCHAR szDateTime[64];
      RECT rcClient;
      HBITMAP hBitmap;

      if (GetCurrentDateTime(szDateTime, ARRAYSIZE(szDateTime)) == 0) {
        MessageBox(hwnd, _T("Failed to get current date time!"), _T("Error"),
                   MB_OK | MB_ICONERROR);
        return;
      }

      GetClientRect(hwnd, &rcClient);

      hBitmap = ReadPixelsToHBITMAP(g_hDC, 0, 0, rcClient.right - rcClient.left,
                                    rcClient.bottom - rcClient.top, FALSE);
      if (hBitmap == NULL) {
        MessageBox(hwnd, _T("Failed to take a snapshot of current window!"),
                   _T("Error"), MB_OK | MB_ICONERROR);
        return;
      }

      _tcscpy(szFileName, _T("Snapshot-"));
      _tcscat(szFileName, szDateTime);
      _tcscat(szFileName, _T(".bmp"));

      EasyCreateBMPFile(szFileName, hBitmap, g_hDC);

      DeleteBitmap(hBitmap);
    } break;
    default:
      break;
  }
}

static void OnSize(HWND hwnd, UINT state, int cx, int cy) {
  int x = 0;
  int y = 0;

  if (cx > cy) {
    x = (cx - cy) / 2;
    cx = cy;
  } else if (cy > cx) {
    y = (cy - cx) / 2;
    cy = cx;
  }

  glViewport(x, y, cx, cy);
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                   LPARAM lParam) {
  switch (uMsg) {
    HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
    HANDLE_MSG(hwnd, WM_KEYDOWN, OnKey);
    HANDLE_MSG(hwnd, WM_SIZE, OnSize);
    default:
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

  return 0;
}

static void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC) {
  PIXELFORMATDESCRIPTOR pfd;

  int iFormat;

  /* get the device context (DC) */
  *hDC = GetDC(hwnd);

  /* set the pixel format for the DC */
  ZeroMemory(&pfd, sizeof(pfd));

  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;

  iFormat = ChoosePixelFormat(*hDC, &pfd);

  SetPixelFormat(*hDC, iFormat, &pfd);

  /* create and enable the render context (RC) */
  *hRC = wglCreateContext(*hDC);

  wglMakeCurrent(*hDC, *hRC);
}

static void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hRC);
  ReleaseDC(hwnd, hDC);
}

// References:
// https://stackoverflow.com/questions/5261299/static-keyword-in-function-declaration-can-be-missing-in-function-definition
