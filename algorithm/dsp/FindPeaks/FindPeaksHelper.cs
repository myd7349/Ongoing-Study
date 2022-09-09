namespace DSP
{
    using System;
    using System.Linq;
    using System.Runtime.InteropServices;

    public static class FindPeaksHelper
    {
        public enum EdgeType
        {
            EdgeNone,
            EdgeRising,
            EdgeFalling,
            EdgeBoth
        }

        public static int[] FindPeaks(double[] data,
            double mph = double.NaN, int mpd = 1, double threshold = 0.0,
            EdgeType edgeType = EdgeType.EdgeRising,
            bool kpsh = false, bool valley = false)
        {
            if (data == null)
                throw new ArgumentNullException("data");

            if (data.Length == 0)
                throw new ArgumentException("data");

            var peaks = new IntPtr[data.Length];
#if false
            var peaksCount = FindPeaks(data, new IntPtr(data.Length), peaks,
                mph, mpd, threshold, edgeType, kpsh, valley);

            return peaks
                .Take(peaksCount.ToInt32())
                .Select(position => position.ToInt32())
                .ToArray();
#else
            var peaksCount = FindPeaks(data, (nuint)data.Length, peaks,
                mph, mpd, threshold, edgeType, kpsh, valley);

            return peaks
                .Take((int)peaksCount)
                .Select(position => position.ToInt32())
                .ToArray();
#endif
        }

#if false
        [DllImport("FindPeaksNative.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "FindPeaks")]
        private static extern IntPtr FindPeaks(
            [In] double[] data, IntPtr length, [Out] IntPtr[] peaks,
            double mph, int mpd, double threshold, EdgeType edgeType,
            [MarshalAs(UnmanagedType.U1)] bool kpsh,
            [MarshalAs(UnmanagedType.U1)] bool valley);
#else
        [DllImport("FindPeaksNative.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "FindPeaks")]
        private static extern nuint FindPeaks(
            [In] double[] data, nuint length, [Out] IntPtr[] peaks,
            double mph, nint mpd, double threshold, EdgeType edgeType,
            [MarshalAs(UnmanagedType.U1)] bool kpsh,
            [MarshalAs(UnmanagedType.U1)] bool valley);
#endif
    }
}

// References:
// [.NET equivalent of size_t](https://stackoverflow.com/questions/772531/net-equivalent-of-size-t)
// [CA1414: Mark boolean P/Invoke arguments with MarshalAs](https://docs.microsoft.com/en-us/visualstudio/code-quality/ca1414?view=vs-2019)
// https://github.com/MicrosoftDocs/visualstudio-docs/blob/master/docs/code-quality/ca1414.md
// [How to marshal a C++ enum in C#](https://stackoverflow.com/questions/22176159/how-to-marshal-a-c-enum-in-c-sharp)
// [C# Marshalling bool](https://stackoverflow.com/questions/32110152/c-sharp-marshalling-bool)
// [Correct way to marshal SIZE_T*?](https://stackoverflow.com/questions/1309509/correct-way-to-marshal-size-t)
// [Convert intptr to ulong array](https://stackoverflow.com/questions/31349268/convert-intptr-to-ulong-array)
// https://github.com/reneschulte/WriteableBitmapEx/blob/master/Source/WriteableBitmapEx.Wpf/NativeMethods.cs
// https://referencesource.microsoft.com/#UIAutomationClientsideProviders/MS/Win32/UnsafeNativeMethods.cs,63
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/UIAutomation/UIAutomationClientSideProviders/MS/Win32/UnsafeNativeMethods.cs
// > internal static extern bool ReadProcessMemory(MS.Internal.AutomationProxies.SafeProcessHandle hProcess, IntPtr Source, IntPtr Dest, IntPtr /*SIZE_T*/ size, out IntPtr /*SIZE_T*/ bytesRead);
