using System;
using System.Windows.Forms;
using System.Windows.Input;

namespace ShortcutKeyDemo
{
    public static class KeyGestureExtension
    {
        public static Keys ToKeys(this KeyGesture keyGesture)
        {
            if (keyGesture == null)
                return Keys.None;

            var keys = Keys.None;

            if (keyGesture.Modifiers.HasFlag(ModifierKeys.Control))
                keys |= Keys.Control;

            if (keyGesture.Modifiers.HasFlag(ModifierKeys.Alt))
                keys |= Keys.Alt;

            if (keyGesture.Modifiers.HasFlag(ModifierKeys.Shift))
                keys |= Keys.Shift;

            if (keyGesture.Modifiers.HasFlag(ModifierKeys.Windows))
                keys |= Keys.LWin;

            switch (keyGesture.Key)
            {
                case Key key when key >= Key.A && key <= Key.Z:
                    keys |= Keys.A + (key - Key.A);
                    return keys;
                case Key key when key >= Key.F1 && key <= Key.F24:
                    keys |= Keys.F1 + (key - Key.F1);
                    return keys;
                case Key key when key >= Key.D0 && key <= Key.D9:
                    keys |= Keys.D0 + (key - Key.D0);
                    return keys;
                case Key key when key >= Key.NumPad0 && key <= Key.NumPad9:
                    keys |= Keys.NumPad0 + (key - Key.NumPad0);
                    return keys;
            }

            throw new NotImplementedException(keyGesture.ToString());
        }
    }
}
