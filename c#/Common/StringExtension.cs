namespace Common
{
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
    }
}
