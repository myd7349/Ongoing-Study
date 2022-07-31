// A modified version of https://github.com/Tyrrrz/LightBulb/blob/master/LightBulb/Views/Controls/HotKeyTextBox.cs
// Blog: [Hotkey Editor Control in WPF](https://tyrrrz.me/blog/hotkey-editor-control-in-wpf)
/*
 LightBulb
 Copyright (C) 2017-2022 Oleksii Holub

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Common.WPF
{
    public class HotKeyTextBox : TextBox
    {
        public HotKeyTextBox()
        {
            IsReadOnly = true;
            IsReadOnlyCaretVisible = false;
            IsUndoEnabled = false;

            if (ContextMenu != null)
                ContextMenu.Visibility = Visibility.Collapsed;

            Text = HotKey?.ToString() ?? string.Empty;
        }

        public KeyGesture HotKey
        {
            get => (KeyGesture)GetValue(HotKeyProperty);
            set => SetValue(HotKeyProperty, value);
        }

        public static readonly DependencyProperty HotKeyProperty = DependencyProperty.Register(
            nameof(HotKey),
            typeof(KeyGesture),
            typeof(HotKeyTextBox),
            new FrameworkPropertyMetadata(
                default(KeyGesture),
                FrameworkPropertyMetadataOptions.BindsTwoWayByDefault,
                HotKeyChanged
            )
        );

        private static void HotKeyChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
        {
            if (sender is HotKeyTextBox control)
                control.Text = control.HotKey?.ConvertToString() ?? string.Empty;
        }

        protected override void OnPreviewKeyDown(KeyEventArgs e)
        {
            e.Handled = true;

            // Get modifiers and key data
            var modifiers = Keyboard.Modifiers;
            var key = e.Key;

            // If nothing was pressed - return
            if (key == Key.None)
                return;

            // If Alt is used as modifier - the key needs to be extracted from SystemKey
            if (key == Key.System)
                key = e.SystemKey;

            // If Delete/Backspace/Escape is pressed without modifiers - clear current value and return
            if ((key == Key.Delete || key == Key.Back || key == Key.Escape) && modifiers == ModifierKeys.None)
            {
                HotKey = new KeyGesture(Key.None);
                return;
            }

            // If the only key pressed is one of the modifier keys - return
            if (key.IsModifierKey())
                return;

            switch (key)
            {
                case Key.Clear:
                case Key.OemClear:
                case Key.Apps:
                    return;
            }

            // If Enter/Space/Tab is pressed without modifiers - return
            if ((key == Key.Enter || key == Key.Space || key == Key.Tab) && modifiers == ModifierKeys.None)
                return;

            // If key has a character and pressed without modifiers or only with Shift - return
            if (HasKeyChar(key) &&
                (modifiers == ModifierKeys.None || modifiers == ModifierKeys.Shift))
                return;

            // Set value
            HotKey = new KeyGesture(key, modifiers);
        }

        private static bool HasKeyChar(Key key)
        {
            switch (key)
            {
                case Key k when k >= Key.A && k <= Key.Z:
                    return true;
                case Key k when k >= Key.D0 && k <= Key.D9:
                    return true;
                case Key k when k >= Key.NumPad0 && k <= Key.NumPad9:
                    return true;
                case Key.OemQuestion:
                case Key.OemQuotes:
                case Key.OemPlus:
                case Key.OemOpenBrackets:
                case Key.OemCloseBrackets:
                case Key.OemMinus:
                case Key.DeadCharProcessed:
                case Key.Oem1:
                case Key.Oem5:
                //case Key.Oem7:
                case Key.OemPeriod:
                case Key.OemComma:
                case Key.Add:
                case Key.Divide:
                case Key.Multiply:
                case Key.Subtract:
                case Key.Oem102:
                case Key.Decimal:
                    return true;
            }

            return false;
        }
    }
}


// References:
// https://github.com/PixiEditor/PixiEditor/blob/master/src/PixiEditor/Views/UserControls/ShortcutBox.cs
// https://github.com/PixiEditor/PixiEditor/blob/master/src/PixiEditor/Views/UserControls/KeyCombinationBox.xaml
// https://github.com/Flow-Launcher/Flow.Launcher/blob/dev/Flow.Launcher/HotkeyControl.xaml
