// 2015-11-24T14:54+08:00
#pragma once

#include "Common.h"
#include "Noncopyable.h"

#include <memory>

namespace Mag
{
namespace Utility
{

class GdiplusInitializer : private Noncopyable
{
public:
    GdiplusInitializer();
    ~GdiplusInitializer();

    BOOL IsInitialized() { return m_bInitialized; }
    BOOL Initialize();
    void Release();

private:
    BOOL m_bInitialized;
    Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
    ULONG_PTR m_ulpGdiplusToken;
};

class GdiplusConsumer : private Noncopyable
{
protected:
    GdiplusConsumer();

private:
    std::shared_ptr<GdiplusInitializer> m_GdiplusInitializer;
};

inline Gdiplus::Color RGBToColor(COLORREF rgb)
{
    Gdiplus::Color color;
    color.SetFromCOLORREF(rgb);

    return color;
}

inline Gdiplus::PointF POINTToPointF(const POINT &pt)
{
    return Gdiplus::PointF((Gdiplus::REAL)pt.x, (Gdiplus::REAL)pt.y);
}

} // namespace Utility
} // namespace Mag