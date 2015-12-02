#include "Common.h"
#include "Utility.h"

namespace Mag
{
namespace Utility
{

void SetClientSize(HWND hwnd, int width, int height)
{
    ASSERT_VALID(hwnd);
    ASSERT(width > 32 && height > 32);

    RECT rcWindow;
    RECT rcClient;

    VERIFY(GetWindowRect(hwnd, &rcWindow));
    VERIFY(GetClientRect(hwnd, &rcClient));

    int cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
    int cy = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

    width += cx;
    height += cy;

    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, width, height, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
    FORWARD_WM_SIZE(hwnd, SIZE_RESTORED, width, height, SendMessage);
}

} // namespace Utility
} // namespace Mag