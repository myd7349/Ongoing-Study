namespace Common
{
    using System;
    using System.Diagnostics;

    public static class StringExtension
    {
        public static bool IsNull(this string str)
        {
            return str == null;
        }

        public static bool IsEmpty(this string str)
        {
            Debug.Assert(!str.IsNull());
            return string.IsNullOrEmpty(str);
        }

        public static bool IsNullOrEmpty(this string str)
        {
            return string.IsNullOrEmpty(str);
        }

        public static bool IsNullOrWhiteSpace(this string str)
        {
            return string.IsNullOrWhiteSpace(str);
        }

        public static string[] Split(this string str, string separator, int count, StringSplitOptions options)
        {
            Debug.Assert(str != null);

            if (str.Length == 1)
                return str.Split(new char[] { str[0] }, count, options);
            else
                return str.Split(new string[] { str }, count, options);
        }
    }
}


// References:
// https://stackoverflow.com/questions/2245442/c-sharp-split-a-string-by-another-string
// https://zhuanlan.zhihu.com/p/30653282
