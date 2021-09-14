#pragma once

#include <gdiplus.h>


#pragma comment(lib, "gdiplus.lib")


class GdiplusInitializer
{
public:
    GdiplusInitializer()
        : m_bInitialized(FALSE)
    {
        Initialize();
    }

    ~GdiplusInitializer()
    {
        Release();
    }

    BOOL IsInitialized() const
    {
        return m_bInitialized;
    }

    BOOL Initialize()
    {
        if (!m_bInitialized)
        {
            m_bInitialized = Gdiplus::Ok ==
                Gdiplus::GdiplusStartup(&m_ulpGdiplusToken, &m_gdiplusStartupInput, NULL);
        }

        return m_bInitialized;
    }

    void Release()
    {
        if (m_bInitialized)
        {
            Gdiplus::GdiplusShutdown(m_ulpGdiplusToken);
            m_bInitialized = FALSE;
        }
    }

private:
    BOOL m_bInitialized;
    Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
    ULONG_PTR m_ulpGdiplusToken;
};



inline Gdiplus::Rect RECTToRect(const RECT &rc)
{
    return Gdiplus::Rect(
        static_cast<INT>(rc.left),
        static_cast<INT>(rc.top),
        static_cast<INT>(rc.right - rc.left),
        static_cast<INT>(rc.bottom - rc.top));
}


inline Gdiplus::RectF RECTToRectF(const RECT &rc)
{
    return Gdiplus::RectF(
        static_cast<Gdiplus::REAL>(rc.left),
        static_cast<Gdiplus::REAL>(rc.top),
        static_cast<Gdiplus::REAL>(rc.right - rc.left),
        static_cast<Gdiplus::REAL>(rc.bottom - rc.top));
}
