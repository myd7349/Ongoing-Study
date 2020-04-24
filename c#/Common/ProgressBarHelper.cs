namespace Common.WinForms
{
    using System;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    public enum ProgressBarState
    {
        Normal = 1, /// Green
        Error = 2, // Red
        Warning = 3, // Yellow
    }

    public static class ProgressBarHelper
    {
        public static void SetState(this ProgressBar pBar, ProgressBarState state)
        {
            SendMessage(pBar.Handle, 1040, (IntPtr)state, IntPtr.Zero);
        }

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr w, IntPtr l);
    }
}

// References:
// [How to change the color of progressbar in C# .NET 3.5?](https://stackoverflow.com/questions/778678/how-to-change-the-color-of-progressbar-in-c-sharp-net-3-5)
