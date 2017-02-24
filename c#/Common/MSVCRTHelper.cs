// 2017-02-23T20:30+08:00
using System;
using System.Runtime.InteropServices;

namespace Common
{
    public static class MSVCRTHelper
    {
        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern double strtod(string value, IntPtr endptr);
    }
}
