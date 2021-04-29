namespace EnumWindowsDotnetCore
{
    using System;
    using System.ComponentModel;
    using System.Runtime.InteropServices;

    using Microsoft.Windows.Sdk;

    class Program
    {
        static void Main(string[] args)
        {
            PInvoke.EnumWindows(EnumWindowsCallback, (LPARAM)IntPtr.Zero);
        }

        static string GetWindowText(HWND hWnd)
        {
            var maxLength = PInvoke.GetWindowTextLength(hWnd);
            if (maxLength == 0)
            {
                // NativeMethods.txt(1,1,1,13): warning PInvoke003: This API will not be generated.
                // Do not generate GetLastError. Call Marshal.GetLastWin32Error() instead.
                // Learn more from https://docs.microsoft.com/dotnet/api/system.runtime.interopservices.marshal.getlastwin32error
                //var lastError = PInvoke.GetLastError();

                var lastError = Marshal.GetLastWin32Error();
                if (lastError != 0)
                {
                    throw new Win32Exception(lastError);
                }

                return string.Empty;
            }

            var text = new char[maxLength + 1];
            unsafe
            {
                fixed (char *lpString = text)
                {
                    var finalLength = PInvoke.GetWindowText(hWnd, lpString, maxLength + 1);
                    if (finalLength == 0)
                    {
                        var lastError = Marshal.GetLastWin32Error();
                        if (lastError != 0)
                        {
                            throw new Win32Exception(lastError);
                        }

                        return string.Empty;
                    }

                    return new string(lpString, 0, finalLength);
                }
            }
        }

        static string GetWindowTextV2(HWND hWnd)
        {
            var cch = PInvoke.GetWindowTextLength(hWnd);
            Span<char> text = stackalloc char[cch + 1];

            unsafe
            {
                fixed (char* lpString = text)
                {
                    PInvoke.GetWindowText(hWnd, lpString, cch + 1);
                }
            }

            return text.ToString();
        }

        static BOOL EnumWindowsCallback(HWND hWnd, LPARAM lParam)
        {
            Console.WriteLine($"{(IntPtr)hWnd} - \"{GetWindowTextV2(hWnd)}\"");

            return true;
        }
    }
}


// References:
// [New Source Generator based approach to getting all the Win32 methods and types you need](https://github.com/dotnet/pinvoke/issues/565)
// [Making Win32 APIs More Accessible to More Languages](https://blogs.windows.com/windowsdeveloper/2021/01/21/making-win32-apis-more-accessible-to-more-languages/)
// https://github.com/microsoft/CsWin32
// [SHFileOperation and PCWSTR Bug](https://github.com/microsoft/CsWin32/issues/228)
// [Friendly overload should expose [In, Out] PWSTR in more friendly way](https://github.com/microsoft/CsWin32/issues/144)
// [CA1838: Avoid StringBuilder parameters for P/Invokes](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1838)
// Ongoing-Study\c#\Console\PInvoke\FunctionPointerTest
// https://github.com/dotnet/pinvoke/blob/bc93e82c2208023ac142acb6a2a26ca3f59fc40a/src/User32/User32.Helpers.cs#L305-L342
// [Is there an enumeration for system error codes in .Net framework?](https://stackoverflow.com/questions/6984959/is-there-an-enumeration-for-system-error-codes-in-net-framework)
