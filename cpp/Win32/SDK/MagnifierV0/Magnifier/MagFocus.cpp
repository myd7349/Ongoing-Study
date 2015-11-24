#include "stdafx.h"
#include "MagFocus.h"
#include "Common/GdiplusHelper.h"
#include "Common/Utility.h"


namespace Mag
{
Focus::Focus(int nSize, COLORREF color)
    : m_nSize(nSize), m_Pen(Utility::RGBToColor(color), 2.0f)
{
}


void Focus::SetColor(COLORREF color)
{
    VERIFY(Gdiplus::Ok == m_Pen.SetColor(Utility::RGBToColor(color)));
}


COLORREF Focus::GetColor() const
{
    Gdiplus::Color color;
    VERIFY(Gdiplus::Ok == m_Pen.GetColor(&color));

    return color.ToCOLORREF();
}


void FocusCross::Draw(Gdiplus::Graphics &graphics, const Gdiplus::PointF &ptCenter)
{
    float fHalfSize = m_nSize / 2.0f;

    graphics.DrawLine(&m_Pen, 
        ptCenter.X - fHalfSize, ptCenter.Y, ptCenter.X + fHalfSize, ptCenter.Y);
    graphics.DrawLine(&m_Pen, 
        ptCenter.X, ptCenter.Y - fHalfSize, ptCenter.X, ptCenter.Y + fHalfSize);
}


void FocusX::Draw(Gdiplus::Graphics &graphics, const Gdiplus::PointF &ptCenter)
{
    Gdiplus::REAL fHalfSize = std::sqrt(m_nSize * m_nSize / 2.0f);

    graphics.DrawLine(&m_Pen, 
        ptCenter.X - fHalfSize, ptCenter.Y - fHalfSize, 
        ptCenter.X + fHalfSize, ptCenter.Y + fHalfSize);
    graphics.DrawLine(&m_Pen, 
        ptCenter.X - fHalfSize, ptCenter.Y + fHalfSize, 
        ptCenter.X + fHalfSize, ptCenter.Y - fHalfSize);
}


void FocusRect::Draw(Gdiplus::Graphics &graphics, const Gdiplus::PointF &ptCenter)
{
    Gdiplus::REAL fHalfSize = m_nSize / 2.0f;

    graphics.DrawRectangle(&m_Pen, 
        ptCenter.X - fHalfSize, ptCenter.Y - fHalfSize, 
        (Gdiplus::REAL)m_nSize, (Gdiplus::REAL)m_nSize);
}
} // namespace Mag