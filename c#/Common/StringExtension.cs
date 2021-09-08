namespace Common
{
    using System;
    using System.Collections.Generic;
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

        public static int AsInt(this string str)
        {
            int value;
            if (!int.TryParse(str, out value))
                throw new ArgumentException("str");

            return value;
        }

        public static uint AsUInt(this string str)
        {
            uint value;
            if (!uint.TryParse(str, out value))
                throw new ArgumentException("str");

            return value;
        }

        public static long AsLong(this string str)
        {
            long value;
            if (!long.TryParse(str, out value))
                throw new ArgumentException("str");

            return value;
        }

        public static ulong AsULong(this string str)
        {
            ulong value;
            if (!ulong.TryParse(str, out value))
                throw new ArgumentException("str");

            return value;
        }

        public static bool AsBoolean(this string str, string trueLiteral = "true", string falseLiteral = "false")
        {
            Debug.Assert(!string.IsNullOrWhiteSpace(trueLiteral));
            Debug.Assert(!string.IsNullOrWhiteSpace(falseLiteral));
            Debug.Assert(trueLiteral != falseLiteral);

            if (str.IsNull())
                throw new ArgumentNullException("str");

            str.Trim();
            if (str.IsEmpty())
                throw new ArgumentException("str");

            if (str == trueLiteral)
                return true;

            if (str == falseLiteral)
                return false;

            // true/false, True/False
            // yes/no, Yes/No
            // on/off, On/Off
            // 1/0
            switch (str[0])
            {
                case 't':
                case 'T':
                case 'y':
                case 'Y':
                case '1':
                    return true;
                case 'f':
                case 'F':
                case 'n':
                case 'N':
                case '0':
                    return false;
                case 'o':
                case 'O':
                    {
                        var lowerValue = str.ToLower();
                        if (lowerValue == "on")
                            return true;
                        else if (lowerValue == "off")
                            return false;
                    }
                    break;
                default: break;
            }

            throw new ArgumentException("str");
        }

#if true
        public static IEnumerable<string> ToStrings(this string buffer)
        {
            int start = 0;
            int length = 0;

            for (var i = 0; i < buffer.Length; i++)
            {
                if (buffer[i] != '\0')
                {
                    length += 1;
                }
                else
                {
                    if (length > 0)
                    {
                        yield return buffer.Substring(start, length);
                        length = 0;
                    }
                    else
                    {
                        yield break;
                    }

                    start = i + 1;
                }
            }

            if (length > 0)
                yield return buffer.Substring(start, length);
        }
#else
        public static IEnumerable<string> ToStrings(this string buffer, int count)
        {
            List<string> strings = new List<string>();

            int start = 0;
            int length = 0;

            for (var i = 0; i < buffer.Length; i++)
            {
                if (buffer[i] != '\0')
                {
                    length += 1;
                }
                else
                {
                    if (length > 0)
                    {
                        strings.Add(buffer.Substring(start, length));
                        length = 0;
                    }
                    else
                    {
                        break;
                    }

                    start = i + 1;
                }
            }

            if (length > 0)
                strings.Add(buffer.Substring(start, length));

            return strings;
        }
#endif
    }
}


// References:
// https://stackoverflow.com/questions/2245442/c-sharp-split-a-string-by-another-string
// https://zhuanlan.zhihu.com/p/30653282
// https://github.com/dotnet/runtime/blob/1fa304a14a8be27428399bd6f2cc51736cb1515a/src/libraries/Microsoft.Extensions.Configuration/tests/Common/TestStreamHelpers.cs#L108-L117
// https://github.com/commandlineparser/commandline/blob/master/src/CommandLine/Infrastructure/StringExtensions.cs
