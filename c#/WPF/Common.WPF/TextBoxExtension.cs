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


// References:
// [Set the caret/cursor position to the end of the string value WPF textbox](https://stackoverflow.com/questions/2888907/set-the-caret-cursor-position-to-the-end-of-the-string-value-wpf-textbox)
// [Passing event args and sender to the RelayCommand](https://stackoverflow.com/questions/2963830/passing-event-args-and-sender-to-the-relaycommand)
// > I upvoted this because while Henrik is correct in explaining that this shouldn't be done, the world isn't perfect and achieving pure MVVM is sometimes impossible. For instance, if you want a Textbox to select all text when it receives focus, you'll need the TextBox itself to call its SelectAll() member. It's undoubtedly doable in MVVM but it'll create insanely complex code, whereas this solution is, in some situations, "good enough".
