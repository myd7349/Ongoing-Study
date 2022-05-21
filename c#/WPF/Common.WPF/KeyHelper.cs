using System;
using System.Globalization;
using System.Windows.Input;

namespace Common.WPF
{
    public static class KeyHelper
    {
        public static bool IsDefinedKey(this Key key)
        {
            return key >= Key.None && key <= Key.OemClear;
        }

        public static bool IsModifierKey(this Key key)
        {
            switch (key)
            {
                case Key.LeftCtrl:
                case Key.RightCtrl:
                case Key.LeftAlt:
                case Key.RightAlt:
                case Key.LeftShift:
                case Key.RightShift:
                case Key.LWin:
                case Key.RWin:
                    return true;
            }

            return false;
        }

        public static string ConvertToString(this Key key)
        {
            return ConvertToString(key, CultureInfo.InvariantCulture);
        }

        public static string ConvertToString(this Key key, CultureInfo culture)
        {
            if (key == Key.None)
                return string.Empty;

            if (key >= Key.D0 && key <= Key.D9)
                return char.ToString((char)(key - Key.D0 + '0'));

            if (key >= Key.A && key <= Key.Z)
                return char.ToString((char)(key - Key.A + 'A'));

            var keyString = MatchKey(key, culture);
            if (keyString != null)
                return keyString;

            throw new InvalidOperationException(nameof(key));
        }

        public static Key? KeyFromString(string keyString)
        {
            return KeyFromString(keyString, CultureInfo.InvariantCulture);
        }

        public static Key? KeyFromString(string keyString, CultureInfo culture)
        {
            if (string.IsNullOrWhiteSpace(keyString))
                return Key.None;

            keyString = keyString.Trim().ToUpper(culture);

            if (keyString.Length == 1 && char.IsLetterOrDigit(keyString[0]))
            {
                if (char.IsDigit(keyString[0]) && (keyString[0] >= '0' && keyString[0] <= '9'))
                    return Key.D0 + keyString[0] - '0';
                else if (char.IsLetter(keyString[0]) && (keyString[0] >= 'A' && keyString[0] <= 'Z'))
                    return Key.A + keyString[0] - 'A';
                else
                    throw new ArgumentException($"Invalid key string {keyString}.", nameof(keyString));
            }
            else
            {
                var keyFound = (Key)(-1);
                switch (keyString)
                {
                    case "ENTER": keyFound = Key.Return; break;
                    case "ESC": keyFound = Key.Escape; break;
                    case "PGUP": keyFound = Key.PageUp; break;
                    case "PGDN": keyFound = Key.PageDown; break;
                    case "PRTSC": keyFound = Key.PrintScreen; break;
                    case "INS": keyFound = Key.Insert; break;
                    case "DEL": keyFound = Key.Delete; break;
                    case "WINDOWS": keyFound = Key.LWin; break;
                    case "WIN": keyFound = Key.LWin; break;
                    case "LEFTWINDOWS": keyFound = Key.LWin; break;
                    case "RIGHTWINDOWS": keyFound = Key.RWin; break;
                    case "APPS": keyFound = Key.Apps; break;
                    case "APPLICATION": keyFound = Key.Apps; break;
                    case "BREAK": keyFound = Key.Cancel; break;
                    case "BACKSPACE": keyFound = Key.Back; break;
                    case "BKSP": keyFound = Key.Back; break;
                    case "BS": keyFound = Key.Back; break;
                    case "SHIFT": keyFound = Key.LeftShift; break;
                    case "LEFTSHIFT": keyFound = Key.LeftShift; break;
                    case "RIGHTSHIFT": keyFound = Key.RightShift; break;
                    case "CONTROL": keyFound = Key.LeftCtrl; break;
                    case "CTRL": keyFound = Key.LeftCtrl; break;
                    case "LEFTCTRL": keyFound = Key.LeftCtrl; break;
                    case "RIGHTCTRL": keyFound = Key.RightCtrl; break;
                    case "ALT": keyFound = Key.LeftAlt; break;
                    case "LEFTALT": keyFound = Key.LeftAlt; break;
                    case "RIGHTALT": keyFound = Key.RightAlt; break;
                    case "SEMICOLON": keyFound = Key.OemSemicolon; break;
                    case "PLUS": keyFound = Key.OemPlus; break;
                    case "COMMA": keyFound = Key.OemComma; break;
                    case "MINUS": keyFound = Key.OemMinus; break;
                    case "PERIOD": keyFound = Key.OemPeriod; break;
                    case "QUESTION": keyFound = Key.OemQuestion; break;
                    case "TILDE": keyFound = Key.OemTilde; break;
                    case "OPENBRACKETS": keyFound = Key.OemOpenBrackets; break;
                    case "PIPE": keyFound = Key.OemPipe; break;
                    case "CLOSEBRACKETS": keyFound = Key.OemCloseBrackets; break;
                    case "QUOTES": keyFound = Key.OemQuotes; break;
                    case "BACKSLASH": keyFound = Key.OemBackslash; break;
                    case "FINISH": keyFound = Key.OemFinish; break;
                    case "ATTN": keyFound = Key.Attn; break;
                    case "CRSEL": keyFound = Key.CrSel; break;
                    case "EXSEL": keyFound = Key.ExSel; break;
                    case "ERASEEOF": keyFound = Key.EraseEof; break;
                    case "PLAY": keyFound = Key.Play; break;
                    case "ZOOM": keyFound = Key.Zoom; break;
                    case "PA1": keyFound = Key.Pa1; break;
                    default: keyFound = (Key)Enum.Parse(typeof(Key), keyString, true); break;
                }

                if ((int)keyFound != -1)
                    return keyFound;

                return null;
            }
        }

        private static string MatchKey(Key key, CultureInfo culture)
        {
            if (key == Key.None)
                return string.Empty;

            switch (key)
            {
                case Key.Back: return "Backspace";
                case Key.LineFeed: return "Clear";
                case Key.Escape: return "Esc";
            }

            if ((int)key >= (int)Key.None && (int)key <= (int)Key.DeadCharProcessed)
                return key.ToString();
            else
                return null;
        }
    }
}


// References:
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/WindowsBase/System/Windows/Input/KeyConverter.cs
