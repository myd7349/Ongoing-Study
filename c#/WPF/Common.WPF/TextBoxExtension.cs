using System;
using System.Windows.Controls;

namespace Common.WPF
{
    public static class TextBoxExtension
    {
        public static void MoveCaretToEnd(this TextBox textBox)
        {
            if (textBox == null)
                throw new ArgumentNullException(nameof(textBox));

            textBox.CaretIndex = textBox.Text.Length;
        }
    }
}
