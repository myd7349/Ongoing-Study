#include "GdiplusHelper.h"
#include "Singleton.h"
#include "Utility.h"

#pragma comment(lib, "gdiplus.lib")

namespace Mag
{
namespace Utility
{

GdiplusInitializer::GdiplusInitializer()
    : m_bInitialized(FALSE) 
{
    VERIFY(Initialize()); 
}

GdiplusInitializer::~GdiplusInitializer()
{
    Release();
}

BOOL GdiplusInitializer::Initialize()
{
    if (!m_bInitialized)
    {
#ifndef NDEBUG
        //MessageBox(NULL, _T("Initializing..."), _T("Gdiplus"), MB_OK);
#endif

        m_bInitialized = Gdiplus::Ok
            == Gdiplus::GdiplusStartup(&m_ulpGdiplusToken, &m_gdiplusStartupInput, NULL);
    }

    return m_bInitialized;
}


void GdiplusInitializer::Release()
{
    if (m_bInitialized)
    {
#ifndef NDEBUG
        //MessageBox(NULL, _T("Releasing..."), _T("Gdiplus"), MB_OK);
#endif

        Gdiplus::GdiplusShutdown(m_ulpGdiplusToken);
    }
}

GdiplusConsumer::GdiplusConsumer()
{
    m_GdiplusInitializer = Singleton<GdiplusInitializer>::GetInstancePtr();
}

} // namespace Utility
} // namespace Mag
