#include "Canvas.h"

namespace Mag
{
namespace Utility
{

Canvas::Canvas(HDC hdc, int cx, int cy)
    : m_hMemDC(NULL), m_hBmpCanvas(NULL), m_hBmpOld(NULL)
{
    if (hdc != NULL && cx >= 0 && cy >= 0)
    {
        if ((m_hMemDC = CreateCompatibleDC(hdc)) != NULL)
        {
            if ((m_hBmpCanvas = CreateCompatibleBitmap(hdc, cx, cy)) != NULL)
            {
                m_hBmpOld = SelectBitmap(m_hMemDC, m_hBmpCanvas);
            }
            else
            {
                DeleteDC(m_hMemDC);
                m_hMemDC = NULL;
            }
        }
    }
}

Canvas::~Canvas()
{
    if (m_hBmpCanvas != NULL)
    {
        assert(m_hMemDC != NULL);
        SelectBitmap(m_hMemDC, m_hBmpOld);
    }

    if (m_hMemDC != NULL)
    {
        DeleteDC(m_hMemDC);
    }
}

} // namespace Utility
} // namespace Mag