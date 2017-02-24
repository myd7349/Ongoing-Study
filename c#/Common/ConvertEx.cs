// 2017-02-23T20:30+08:00
using System;

// System.Convert.ToDouble("25 mm/s") -> Bang!
// Common.ConvertEx.ToDouble("25 mm/s") -> 25.0

namespace Common
{
    public static class ConvertEx
    {
        public static double ToDouble(string value)
        {
            return MSVCRTHelper.strtod(value, IntPtr.Zero);
        }
    }
}
