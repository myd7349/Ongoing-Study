namespace Common
{
    using System.Linq;

    public static class Base64Helper
    {
        public static bool IsBase64String(string s, bool urlSafe = false)
        {
            int paddingBytes = GetPaddingBytes(s);
            return !string.IsNullOrEmpty(s) && s.Take(s.Length - paddingBytes).All(c => IsBase64Char(c, urlSafe));
        }

        public static bool IsBase64Char(char c, bool urlSafe = false)
        {
            if (IsLetterOrDigit(c))
                return true;

            if (!urlSafe)
                return c == '+' || c == '/';
            else
                return c == '-' || c == '_';
        }

        public static bool IsLetterOrDigit(char c)
        {
#if false
            return char.IsLetterOrDigit(c);
#else
            return c >= 'A' && c <= 'Z' ||
                c >= 'a' && c <= 'z' ||
                c >= '0' && c <= '9';
#endif
        }

        public static int GetPaddingBytes(string s)
        {
            if (s.Length < 4 || s[s.Length - 1] != '=')
                return 0;

            if (s[s.Length - 2] != '=')
                return 1;
            else
                return 2;
        }
    }
}

// References:
// [XAML WPF How to add inline background image on FlowDocument?](https://stackoverflow.com/questions/25557891/xaml-wpf-how-to-add-inline-background-image-on-flowdocument)
