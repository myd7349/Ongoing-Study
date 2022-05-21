using System.Windows;
using System.Windows.Controls;

using Microsoft.Xaml.Behaviors;

namespace Common.WPF.Behaviors
{
    public class PutCursorAtEndTextBoxBehavior : Behavior<UIElement>
    {
        private TextBox _textBox;

        protected override void OnAttached()
        {
            base.OnAttached();

            _textBox = AssociatedObject as TextBox;

            if (_textBox == null)
            {
                return;
            }
            _textBox.GotFocus += TextBoxGotFocus;
        }

        protected override void OnDetaching()
        {
            if (_textBox == null)
            {
                return;
            }
            _textBox.GotFocus -= TextBoxGotFocus;

            base.OnDetaching();
        }

        private void TextBoxGotFocus(object sender, RoutedEventArgs routedEventArgs)
        {
            _textBox.CaretIndex = _textBox.Text.Length;
        }
    }
}


// References:
// [Set the caret/cursor position to the end of the string value WPF textbox](https://stackoverflow.com/questions/2888907/set-the-caret-cursor-position-to-the-end-of-the-string-value-wpf-textbox)
