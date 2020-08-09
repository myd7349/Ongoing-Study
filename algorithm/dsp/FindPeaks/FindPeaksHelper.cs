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
            double mph, int mpd = 1, double threshold = 0.0,
            EdgeType edgeType = EdgeType.EdgeRising,
            bool kpsh = false, bool valley = false)
        {
            if (data == null)
                throw new ArgumentNullException("data");

            if (data.Length == 0)
                throw new ArgumentException("data");

            int[] peaks = new int[data.Length];
            var peaksCount = FindPeaks(data, data.Length, peaks,
                mph, mpd, threshold, edgeType, kpsh, valley);
            return peaks.Take(peaksCount).ToArray();
        }

        [DllImport("FindPeaksNative.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "FindPeaks")]
        private static extern int FindPeaks([In] double[] data, int length, [Out] int[] peaks,
            double mph, int mpd, double threshold, EdgeType edgeType,
            [MarshalAs(UnmanagedType.U1)] bool kpsh,
            [MarshalAs(UnmanagedType.U1)] bool valley);
    }
}

// References:
// [.NET equivalent of size_t](https://stackoverflow.com/questions/772531/net-equivalent-of-size-t)
// [CA1414: Mark boolean P/Invoke arguments with MarshalAs](https://docs.microsoft.com/en-us/visualstudio/code-quality/ca1414?view=vs-2019)
// https://github.com/MicrosoftDocs/visualstudio-docs/blob/master/docs/code-quality/ca1414.md
// [How to marshal a C++ enum in C#](https://stackoverflow.com/questions/22176159/how-to-marshal-a-c-enum-in-c-sharp)
// [C# Marshalling bool](https://stackoverflow.com/questions/32110152/c-sharp-marshalling-bool)
