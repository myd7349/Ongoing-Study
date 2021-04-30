//#define USE_STRINGBUILDER

namespace FunctionPointerTest
{
    using System;
    using static System.Console;

#if USE_STRINGBUILDER
    using System.Runtime.InteropServices;
    using System.Text;
#endif

    using PInvoke;
    using static PInvoke.User32;

    using Common;

    class Program
    {
#if !USE_STRINGBUILDER
        static int count = 0;
#endif

        static void Main(string[] args)
        {
#if USE_STRINGBUILDER
            var unmanagedBuffer = new UnmanagedBuffer(sizeof(int));
            Marshal.WriteInt32(unmanagedBuffer, 0);

            EnumWindows(new WNDENUMPROC(EnumWindowsCallback), unmanagedBuffer);
            WriteLine($"Total top-level windows count: {Marshal.ReadInt32(unmanagedBuffer)}");
#else
            EnumWindows(EnumWindowsCallback, IntPtr.Zero);
            WriteLine($"Total top-level windows count: {count}");
#endif

            ReadKey();
        }

#if USE_STRINGBUILDER
        // Note:
        // This shows how to use StringBuilder for PInvoke.
        // In real projects, do not do this, use PInvoke.User32.GetWindowText instead.
        [DllImport("User32.dll")]
        internal static extern void GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

        static bool EnumWindowsCallback(IntPtr hwnd, IntPtr lParam)
        {
            try
            {
                var cch = GetWindowTextLength(hwnd);
                var text = new StringBuilder(cch);
                GetWindowText(hwnd, text, text.Capacity + 1);

                WriteLine($"{hwnd} - \"{text}\"");
            }
            catch (Win32Exception exc)
            {
                WriteLine($"{hwnd} - {exc.ToString()}");
            }

            Marshal.WriteInt32(lParam, Marshal.ReadInt32(lParam) + 1);

            return true;
        }
#else
        static bool EnumWindowsCallback(IntPtr hwnd, IntPtr lParam)
        {
            try
            {
                WriteLine($"{hwnd} - \"{GetWindowText(hwnd)}\"");
            }
            catch (Win32Exception exc)
            {
                WriteLine($"{hwnd} - {exc.ToString()}");
            }

            ++count;

            return true;
        }
#endif
    }
}

// References:
// [UnmanagedFunctionPointer - FreeRDP example](https://github.com/FreeRDP/FreeRDP-Sharp/blob/0334b0dcc785243ba752b1731f123212a733fdc2/FreeRDP/Core/FreeRDP.cs#L25)
// [Correct user of StringBuilder for PInvoke](https://social.msdn.microsoft.com/Forums/vstudio/en-US/f36d2198-1d4f-4224-a146-97e20f20c2f1/correct-user-of-stringbuilder-for-pinvoke?forum=csharpgeneral)
// > For example, if you initialize a StringBuilder buffer to a capacity of N,
//   the marshaler provides a buffer of size (N+1) characters. The +1 accounts
//   for the fact that the unmanaged string has a null terminator while StringBuilder does not.
// [Default Marshaling for Strings](https://docs.microsoft.com/en-us/dotnet/framework/interop/default-marshaling-for-strings?redirectedfrom=MSDN)
// [CA1838: Avoid StringBuilder parameters for P/Invokes](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1838)
// https://github.com/dotnet/pinvoke/blob/bc93e82c2208023ac142acb6a2a26ca3f59fc40a/src/User32/User32.Helpers.cs#L305-L342
