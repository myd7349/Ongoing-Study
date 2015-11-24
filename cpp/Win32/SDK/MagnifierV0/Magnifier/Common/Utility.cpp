#include "Common.h"
#include "Utility.h"

namespace Mag
{
namespace Utility
{

void SetClientSize(HWND hwnd, int width, int height)
{
    assert(IsWindow(hwnd));
    assert(width > 32 && height > 32);

    RECT rcWindow;
    RECT rcClient;

    GetWindowRect(hwnd, &rcWindow);
    GetClientRect(hwnd, &rcClient);

    int cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
    int cy = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

    width += cx;
    height += cy;

    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, width, height, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

} // namespace Utility
} // namespace Mag