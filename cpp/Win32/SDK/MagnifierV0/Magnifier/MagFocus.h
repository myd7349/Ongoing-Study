// 2015-11-20T13:06+08:00
#pragma once

#include "Common/GdiplusHelper.h"


namespace Mag
{

class Focus : private Utility::GdiplusConsumer
{
public:
    Focus(int nSize, COLORREF rgb);
    virtual ~Focus() {}

    virtual void Draw(Gdiplus::Graphics &graphics, const Gdiplus::PointF &ptCenter) = 0;

    void SetSize(int nSize) { m_nSize = nSize; }
    int GetSize() const { return m_nSize; }

    void SetColor(COLORREF color);
    COLORREF GetColor() const;

protected:
    int m_nSize;
    Gdiplus::Pen m_Pen;
};


class CrossFocus : public Focus
{
public:
    CrossFocus(int nSize, COLORREF rgb) : Focus(nSize, rgb) {}

    void Draw(Gdiplus::Graphics &graphics, const Gdiplus::PointF &ptCenter);
};


class XFocus : public Focus
{
public:
    XFocus(int nSize, COLORREF rgb) : Focus(nSize, rgb) {}

    void Draw(Gdiplus::Graphics &graphics, const Gdiplus::PointF &ptCenter);
};


class RectFocus : public Focus
{
public:
    RectFocus(int nSize, COLORREF rgb) : Focus(nSize, rgb) {}

    void Draw(Gdiplus::Graphics &graphics, const Gdiplus::PointF &ptCenter);
};

} // namespace Mag