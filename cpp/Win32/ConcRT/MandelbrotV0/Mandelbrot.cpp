// Mandelbrot.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "Mandelbrot.h"


typedef std::shared_ptr<Gdiplus::Bitmap> BitmapPtr;


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawMandelbrot(BitmapPtr bitmap);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    GdiplusInitializer gdiplusInitializer;

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MANDELBROT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MANDELBROT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MANDELBROT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MANDELBROT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: Add any drawing code that uses hdc here...
            RECT rcClient;
            GetClientRect(hWnd, &rcClient);

            int width = static_cast<int>(rcClient.right - rcClient.left);
            int height = static_cast<int>(rcClient.bottom - rcClient.top);

            if (width > 0 && height > 0)
            {
                BitmapPtr bitmap = std::make_shared<Gdiplus::Bitmap>(width, height);
                if (bitmap != nullptr)
                {
                    DrawMandelbrot(bitmap);

                    Gdiplus::Graphics graphics(hdc);
                    graphics.DrawImage(bitmap.get(), RECTToRectF(rcClient));
                }
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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


void DrawMandelbrot(BitmapPtr bitmap)
{
    if (bitmap == nullptr)
        return;

    // Get the size of the bitmap.
    const UINT width = bitmap->GetWidth();
    const UINT height = bitmap->GetHeight();

    // Return if either width or height is zero.
    if (width == 0 || height == 0)
        return;

    // Lock the bitmap into system memory.
    Gdiplus::BitmapData bitmapData;
    Gdiplus::Rect rectBmp(0, 0, width, height);
    bitmap->LockBits(&rectBmp, Gdiplus::ImageLockModeWrite, PixelFormat32bppRGB,
        &bitmapData);

    // Obtain a pointer to the bitmap bits.
    int* bits = reinterpret_cast<int*>(bitmapData.Scan0);

    // Real and imaginary bounds of the complex plane.
    double re_min = -2.1;
    double re_max = 1.0;
    double im_min = -1.3;
    double im_max = 1.3;

    // Factors for mapping from image coordinates to coordinates on the complex plane.
    double re_factor = (re_max - re_min) / (width - 1);
    double im_factor = (im_max - im_min) / (height - 1);

    // The maximum number of iterations to perform on each point.
    const UINT max_iterations = 1000;

    // Compute whether each point lies in the Mandelbrot set.
    for (UINT row = 0u; row < height; ++row)
    {
        // Obtain a pointer to the bitmap bits for the current row.
        int* destPixel = bits + (row * width);

        // Convert from image coordinate to coordinate on the complex plane.
        double y0 = im_max - (row * im_factor);

        for (UINT col = 0u; col < width; ++col)
        {
            // Convert from image coordinate to coordinate on the complex plane.
            double x0 = re_min + col * re_factor;

            double x = x0;
            double y = y0;

            UINT iter = 0;
            double x_sq, y_sq;
            while (iter < max_iterations && ((x_sq = x * x) + (y_sq = y * y) < 4))
            {
                double temp = x_sq - y_sq + x0;
                y = 2 * x * y + y0;
                x = temp;
                ++iter;
            }

            // If the point is in the set (or approximately close to it), color
            // the pixel black.
            if (iter == max_iterations)
            {
                *destPixel = 0;
            }
            // Otherwise, select a color that is based on the current iteration.
            else
            {
                BYTE red = static_cast<BYTE>((iter % 64) * 4);
                *destPixel = red << 16;
            }

            // Move to the next point.
            ++destPixel;
        }
    }

    // Unlock the bitmap from system memory.
    bitmap->UnlockBits(&bitmapData);
}


// References:
// [Walkthrough: Create a traditional Windows Desktop application (C++)](https://docs.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-160&viewFallbackFrom=vs-2019#feedback)
// [Walkthrough: Removing Work from a User-Interface Thread](https://docs.microsoft.com/en-us/cpp/parallel/concrt/walkthrough-removing-work-from-a-user-interface-thread?view=msvc-160)
// https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/parallel/concrt/walkthrough-removing-work-from-a-user-interface-thread.md
