using System;
using System.Globalization;
using System.Windows.Input;

namespace Common.WPF
{
    public static class ModifierKeysHelper
    {
        public static string ConvertToString(this ModifierKeys modifierKeys)
        {
            if (!ModifierKeysConverter.IsDefinedModifierKeys(modifierKeys))
                throw new ArgumentException(nameof(modifierKeys));

            var strModifiers = string.Empty;

            if ((modifierKeys & ModifierKeys.Control) == ModifierKeys.Control)
                strModifiers += MatchModifiers(ModifierKeys.Control);

            if ((modifierKeys & ModifierKeys.Alt) == ModifierKeys.Alt)
            {
                if (strModifiers.Length > 0)
                    strModifiers += Modifier_Delimiter;

                strModifiers += MatchModifiers(ModifierKeys.Alt);
            }

            if ((modifierKeys & ModifierKeys.Windows) == ModifierKeys.Windows)
            {
                if (strModifiers.Length > 0)
                    strModifiers += Modifier_Delimiter;

                strModifiers += MatchModifiers(ModifierKeys.Windows); ;
            }

            if ((modifierKeys & ModifierKeys.Shift) == ModifierKeys.Shift)
            {
                if (strModifiers.Length > 0)
                    strModifiers += Modifier_Delimiter;

                strModifiers += MatchModifiers(ModifierKeys.Shift); ;
            }

            return strModifiers;
        }

        public static ModifierKeys ModifierKeysFromString(string strModifiers)
        {
            strModifiers = strModifiers?.Trim();

            if (string.IsNullOrEmpty(strModifiers))
                return ModifierKeys.None;

            var modifiers = ModifierKeys.None;
            if (strModifiers.Length != 0)
            {
                int offset = 0;
                do
                {
                    offset = strModifiers.IndexOf(Modifier_Delimiter);
                    var token = (offset < 0) ? strModifiers : strModifiers.Substring(0, offset);
                    token = token.Trim();
                    token = token.ToUpper(CultureInfo.InvariantCulture);

                    if (token == string.Empty)
                        break;

                    switch (token)
                    {
                        case "CONTROL":
                        case "CTRL":
                            modifiers |= ModifierKeys.Control;
                            break;
                        case "SHIFT":
                            modifiers |= ModifierKeys.Shift;
                            break;
                        case "ALT":
                            modifiers |= ModifierKeys.Alt;
                            break;
                        case "WINDOWS":
                        case "WIN":
                            modifiers |= ModifierKeys.Windows;
                            break;
                        default:
                            throw new NotSupportedException(nameof(strModifiers));
                    }

                    strModifiers = strModifiers.Substring(offset + 1);
                } while (offset != -1);
            }

            return modifiers;
        }

        internal static string MatchModifiers(ModifierKeys modifierKeys)
        {
            string modifiers = string.Empty;
            switch (modifierKeys)
            {
                case ModifierKeys.Control: modifiers = "Ctrl"; break;
                case ModifierKeys.Shift: modifiers = "Shift"; break;
                case ModifierKeys.Alt: modifiers = "Alt"; break;
                case ModifierKeys.Windows: modifiers = "Windows"; break;
            }
            return modifiers;
        }

        private const char Modifier_Delimiter = '+';
    }
}


// References:
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/WindowsBase/System/Windows/Input/ModifierKeysConverter.cs

