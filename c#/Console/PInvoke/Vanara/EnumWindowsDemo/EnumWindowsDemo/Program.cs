namespace EnumWindowsDemo
{
    using System;
    using System.ComponentModel;
    using System.Text;

    using Vanara.PInvoke;

    class Program
    {
        static void Main(string[] args)
        {
            User32.EnumWindows(EnumWindowsCallback, IntPtr.Zero);
            Console.ReadKey();
        }

        static string GetWindowText(HWND hWnd)
        {
            var maxLength = User32.GetWindowTextLength(hWnd);
            if (maxLength == 0)
            {
                var lastError = Kernel32.GetLastError();
                if (lastError != Win32Error.ERROR_SUCCESS)
                    throw new Win32Exception((int)(uint)lastError);

                return string.Empty;
            }

            var text = new StringBuilder(maxLength);
            var textLength = User32.GetWindowText(hWnd, text, maxLength + 1);
            if (textLength == 0)
            {
                var lastError = Kernel32.GetLastError();
                if (lastError != Win32Error.ERROR_SUCCESS)
                    throw new Win32Exception((int)(uint)lastError);

                return string.Empty;
            }

            text.Length = textLength;
            return text.ToString();
        }

        static bool EnumWindowsCallback(HWND hWnd, IntPtr lParam)
        {
            try
            {
                Console.WriteLine($"{hWnd} - \"{GetWindowText(hWnd)}\"");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{hWnd} -\n{ex}");
            }
            
            return true;
        }
    }
}


// References:
// [CA1838: Avoid StringBuilder parameters for P/Invokes](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1838)
// https://github.com/dotnet/pinvoke/blob/bc93e82c2208023ac142acb6a2a26ca3f59fc40a/src/User32/User32.Helpers.cs#L305-L342
