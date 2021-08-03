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

    public delegate T GenericParse<T>(string s);

    public delegate bool GenericTryParse<T>(string s, out T v);

    public delegate string GenericConvert<T>(T v);
}


// References:
// [Is there any generic Parse() function that will convert a string to any type using parse?](https://stackoverflow.com/questions/3502493/is-there-any-generic-parse-function-that-will-convert-a-string-to-any-type-usi)
// [How to make a Generic Type Cast function](https://stackoverflow.com/questions/6884653/how-to-make-a-generic-type-cast-function)
