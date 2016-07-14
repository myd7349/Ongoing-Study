#include "DrawSineCurve.h"

#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>


inline HPEN CreatePen(const PenProperty &pen)
{
    return CreatePen(pen.Style, pen.Width, pen.Color);
}

inline int RectWidth(const RECT &rc)
{
    return rc.right - rc.left;
}

inline int RectHeight(const RECT &rc)
{
    return rc.bottom - rc.top;
}

void DrawSineCurve(HDC hdc, const RECT &rc, const PenProperty &pen, int xTicksCount)
{
    assert(hdc != NULL);
    assert(xTicksCount > 0);

    if (hdc == NULL || xTicksCount <= 0)
        return;

    int nWidth = RectWidth(rc);
    int nHeight = RectHeight(rc);

    std::vector<POINT> points(xTicksCount + 2);
    POINT ptStart = { rc.left, rc.top + nHeight / 2 };

    // Populate points vector
    double x = 0;
    double xInc = M_PI * 2 / xTicksCount;
    double xFactor = double(nWidth) / xTicksCount;
    double yFactor = nHeight / 2;

    points.front() = ptStart;
    for (auto i = 1U; i < points.size() - 1; ++i)
    {
        points[i].x = ptStart.x + long(i * xFactor);
        points[i].y = ptStart.y - long(sin(x) * yFactor);
        x += xInc;
    }
    points.back() = { rc.right, ptStart.y };

    // Draw the curve
    HPEN hPen = CreatePen(pen);
    HPEN hOldPen = SelectPen(hdc, hPen);
    Polyline(hdc, points.data(), (int)points.size());
    SelectPen(hdc, hOldPen);
    DeletePen(hPen);
}
