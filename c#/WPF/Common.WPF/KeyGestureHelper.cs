using System;
using System.Windows.Input;

namespace Common.WPF
{
    public static class KeyGestureHelper
    {
        public static bool IsSameAs(this KeyGesture keyGesture, KeyGesture otherKeyGesture)
        {
            if (keyGesture == otherKeyGesture)
                return true;

            if (keyGesture != null && otherKeyGesture != null)
                return keyGesture.Key == otherKeyGesture.Key &&
                    keyGesture.Modifiers == otherKeyGesture.Modifiers;

            return false;
        }

        public static string ConvertToString(this KeyGesture keyGesture)
        {
            if (keyGesture == null)
                return string.Empty;

            if (!ModifierKeysConverter.IsDefinedModifierKeys(keyGesture.Modifiers))
                throw new ArgumentException($"Invalid modifiers {keyGesture.Modifiers}.", nameof(keyGesture));

            if (!keyGesture.Key.IsDefinedKey())
                throw new ArgumentException($"Invalid key {keyGesture.Key}.", nameof(keyGesture));

            if (keyGesture.Key == Key.None)
                return string.Empty;


            var strBinding = string.Empty;
            var strKey = keyGesture.Key.ConvertToString();
            if (strKey != string.Empty)
            {
                strBinding += keyGesture.Modifiers.ConvertToString();
                if (strBinding != string.Empty)
                    strBinding += MODIFIERS_DELIMITER;

                strBinding += strKey;

                if (!string.IsNullOrEmpty(keyGesture.DisplayString))
                    strBinding += DISPLAYSTRING_SEPARATOR + keyGesture.DisplayString;
            }

            return strBinding;
        }

        public static KeyGesture KeyGestureFromString(string keyBinding)
        {
            var fullName = keyBinding?.Trim();

            if (string.IsNullOrEmpty(fullName))
                return new KeyGesture(Key.None);

            string keyToken;
            string modifiersToken;
            string displayString;

            // break apart display string
            int index = fullName.IndexOf(DISPLAYSTRING_SEPARATOR);
            if (index >= 0)
            {
                displayString = fullName.Substring(index + 1).Trim();
                fullName = fullName.Substring(0, index).Trim();
            }
            else
            {
                displayString = string.Empty;
            }

            // break apart key and modifiers
            index = fullName.LastIndexOf(MODIFIERS_DELIMITER);
            if (index >= 0)
            {   // modifiers exists
                modifiersToken = fullName.Substring(0, index);
                keyToken = fullName.Substring(index + 1);
            }
            else
            {
                modifiersToken = string.Empty;
                keyToken = fullName;
            }

            var modifiers = ModifierKeys.None;
            var key = KeyHelper.KeyFromString(keyToken);
            if (key != null)
            {
                modifiers = ModifierKeysHelper.ModifierKeysFromString(modifiersToken);
                return new KeyGesture(key.Value, modifiers, displayString);
            }

            throw new ArgumentException(nameof(keyBinding));
        }

        private const char MODIFIERS_DELIMITER = '+';
        internal const char DISPLAYSTRING_SEPARATOR = ',';
    }
}


// References:
// https://github.com/dotnet/wpf/blob/main/src/Microsoft.DotNet.Wpf/src/PresentationCore/System/Windows/Input/Command/KeyGestureConverter.cs
