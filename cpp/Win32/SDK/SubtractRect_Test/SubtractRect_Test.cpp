// 2014-08-20T13:17+08:00
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>

#include <stdio.h>
#include <stdlib.h>

// 论给宏参数加小括号的重要性。
#define PRINT_RECT(rc, newline) \
    _tprintf(_T("(%4d,%4d,%4d,%4d)%c"), (rc).left, (rc).top, (rc).right, (rc).bottom, \
        newline ? '\n' : ' ')

// 之前，我一直以为SubtractRect类似于计算Python中两个集合的差积。

// 还是在线MSDN上讲的清楚：
// file:///E:/doc/msvc/url/SubtractRect/CRect%20SubtractRect.maff
// http://msdn.microsoft.com/zh-cn/library/09k82h2b%28v=vs.110%29.aspx
// 1.
// The subtraction is the smallest rectangle that contains 
// all of the points in lpRectScr1 that are not in the intersection 
// of lpRectScr1 and lpRectScr2.
// 2.
// The rectangle specified by lpRectSrc1 will be unchanged if 
// the rectangle specified by lpRectSrc2 doesn't completely overlap 
// the rectangle specified by lpRectSrc1 in at least one of the 
// x- or y-directions. 
// 3.
//  SubtractRect is not the same as operator - nor operator -=. 
// Neither of these operators ever calls SubtractRect. 

void SubtractRectWrapper(LPRECT lprcRes, LPCRECT lpcrcRect1, LPCRECT lpcrcRect2)
{
    PRINT_RECT(*lpcrcRect1, FALSE);
    _tprintf(_T("- "));
    PRINT_RECT(*lpcrcRect2, FALSE);
    _tprintf(_T("= "));

    SubtractRect(lprcRes, lpcrcRect1, lpcrcRect2);
    PRINT_RECT(*lprcRes, TRUE);
}
int _tmain(int argc, _TCHAR *argv[])
{
    RECT rcRes;
    RECT rcRect1;
    RECT rcRect2;

    // 参见：SubtractRect_Interpretation.png的左侧图形示例
    SetRect(&rcRect1, 10, 10, 100, 100);
    SetRect(&rcRect2, 50, 50, 150, 150);
    SubtractRectWrapper(&rcRes, &rcRect1, &rcRect2);

    // 参见：SubtractRect_Interpretation.png的右侧图形示例
    SetRect(&rcRect2, 50, 10, 150, 150);
    SubtractRectWrapper(&rcRes, &rcRect1, &rcRect2);

    // 计算窗体最大化后的显示区域。
    SetRect(&rcRect1, 0, 0, 
        GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    SetRectEmpty(&rcRect2);
    HWND hTrayWnd = FindWindow(_T("Shell_TrayWnd"), _T(""));
    if (hTrayWnd != NULL) {
        GetWindowRect(hTrayWnd, &rcRect2);
    }
    SubtractRectWrapper(&rcRes, &rcRect1, &rcRect2);

    // rect2 完全包含在rect1内。
    SetRect(&rcRect1, 10, 10, 100, 100);
    SetRect(&rcRect2, 10, 10, 20, 30);
    SubtractRectWrapper(&rcRes, &rcRect1, &rcRect2);

    // rect1完全包含在rect2内。
    SetRect(&rcRect1, 10, 10, 30, 20);
    SetRect(&rcRect2, 10, 10, 100, 100);
    SubtractRectWrapper(&rcRes, &rcRect1, &rcRect2);

    // 总结：
    // 1. 如果从rect1中减去 rect1与rect2的交集 得到的图形是矩形时，返回结果就是
    //    这个矩形。
    // 2. 如果从rect1中减去 rect1与rect2的交集 得到的图形不是矩形（也就是说，
    //    无论在x轴方向上，还是y轴方向上，rect2都不能完全遮住rect1的某一边），
    //    则返回结果为rect1。

    system("pause");

    return 0;
}
