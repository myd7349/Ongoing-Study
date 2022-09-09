// 2017-04-22T19:37:02+08:00
// What?
// A WPF `Keyboard.IsKeyDown` equivalent for WinForms projects.
// How?
// ILSpy + PresentationCore.ni.dll
using System.ComponentModel;
using System.Windows.Forms;

namespace Common.WinForms.Input
{
    public static class Keyboard
    {
        public static bool IsKeyDown(Keys key)
        {
            switch (key)
            {
                case Keys.Control:
                    return IsKeyDownInternal(Keys.LControlKey) || IsKeyDownInternal(Keys.RControlKey);
                case Keys.Shift:
                    return IsKeyDownInternal(Keys.LShiftKey) || IsKeyDownInternal(Keys.RShiftKey);
                case Keys.Alt:
                    return IsKeyDownInternal(Keys.LMenu) || IsKeyDownInternal(Keys.RMenu);
                default: break;
            }

            return IsKeyDownInternal(key);
        }

        private static bool IsKeyDownInternal(Keys key)
        {
            ValidateKey(key);
            return (byte)(GetKeyStatesFromSystem(key) & KeyStates.Down) == 1;
        }

        public static bool IsKeyToggled(Keys key)
        {
            ValidateKey(key);
            return (byte)(GetKeyStatesFromSystem(key) & KeyStates.Toggled) == 2;
        }

        public static bool IsKeyUp(Keys key)
        {
            return !IsKeyDown(key);
        }

        private static void ValidateKey(Keys key)
        {
            if (((Keys)256 <= key || key <= Keys.None)
                && (key != Keys.Control && key != Keys.Alt && key != Keys.Shift))
            {
                throw new InvalidEnumArgumentException("key");
            }
        }

        private static KeyStates GetKeyStatesFromSystem(Keys key)
        {
            KeyStates keyStates = KeyStates.None;
            
            var keyCode = KeyInterop.VirtualKeyFromKey(key);
            var keyState = (int)KeyInterop.GetKeyState(keyCode);
            
            if ((keyState & 32768) == 32768)
            {
                keyStates |= KeyStates.Down;
            }
            
            if ((keyState & 1) == 1)
            {
                keyStates |= KeyStates.Toggled;
            }
            
            return keyStates;
        }
    }
}

// References:
// [How to detect the currently pressed key?](http://stackoverflow.com/questions/1100285/how-to-detect-the-currently-pressed-key)
// [How to detect if any key is pressed](http://stackoverflow.com/questions/12076107/how-to-detect-if-any-key-is-pressed)
// [How can I convert 'System.Windows.Input.Key' to 'System.Windows.Forms.Keys'?](http://stackoverflow.com/questions/1153009/how-can-i-convert-system-windows-input-key-to-system-windows-forms-keys)
// https://github.com/FlaUI/FlaUI/blob/master/src/FlaUI.Core/Input/Keyboard.cs
// https://github.com/gitextensions/gitextensions/blob/master/GitUI/Hotkey/KeysExtensions.cs
// https://github.com/dotnet/winforms/blob/main/src/Microsoft.VisualBasic.Forms/src/Microsoft/VisualBasic/Devices/Keyboard.vb
