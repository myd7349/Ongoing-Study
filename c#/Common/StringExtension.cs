namespace Common
{
    using System;
    using System.Diagnostics;
    using System.IO;

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

        public static Stream ToStream(this string str)
        {
            var memStream = new MemoryStream();
            var textWriter = new StreamWriter(memStream);
            textWriter.Write(str);
            textWriter.Flush();
            memStream.Seek(0, SeekOrigin.Begin);

            return memStream;
        }
    }
}


// References:
// https://stackoverflow.com/questions/2245442/c-sharp-split-a-string-by-another-string
// https://zhuanlan.zhihu.com/p/30653282
// https://github.com/dotnet/runtime/blob/1fa304a14a8be27428399bd6f2cc51736cb1515a/src/libraries/Microsoft.Extensions.Configuration/tests/Common/TestStreamHelpers.cs#L108-L117
