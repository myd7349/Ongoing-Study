using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Interop;

namespace Common.WPF
{
    public static class WindowExtensions
    {
        public static void EnableCloseButton(this Window window, bool enable = true)
        {
            var hwnd = new WindowInteropHelper(window).Handle;
            var hMenu = GetSystemMenu(hwnd, false);
            if (hMenu != IntPtr.Zero)
                EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | (enable ? MF_ENABLED : MF_GRAYED));
        }

        public static void RemoveSysMenu(this Window window)
        {
            var hwnd = new WindowInteropHelper(window).Handle;
            SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SYSMENU);
        }

        private const int GWL_STYLE = -16;
        private const int WS_SYSMENU = 0x80000;
        private const uint MF_BYCOMMAND = 0x00000000;
        private const uint MF_GRAYED = 0x00000001;
        private const uint MF_ENABLED = 0x00000000;
        private const uint SC_CLOSE = 0xF060;
        private const int WM_SHOWWINDOW = 0x00000018;
        private const int WM_CLOSE = 0x10;

        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        [DllImport("user32.dll")]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        [DllImport("user32.dll")]
        private static extern IntPtr GetSystemMenu(IntPtr hWnd, bool bRevert);

        [DllImport("user32.dll")]
        private static extern bool EnableMenuItem(IntPtr hMenu, uint uIDEnableItem, uint uEnable);
    }
}


// References:
// [How to hide close button in WPF window?](https://stackoverflow.com/questions/743906/how-to-hide-close-button-in-wpf-window)
// [How can i disable close button from wpf window ?](https://social.msdn.microsoft.com/Forums/vstudio/en-US/2f503183-86e4-40fa-ba2f-a0d6f741c561/how-can-i-disable-close-button-from-wpf-window-?forum=wpf)
