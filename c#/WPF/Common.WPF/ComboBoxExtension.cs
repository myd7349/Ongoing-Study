using System;
using System.Windows.Controls;

namespace Common.WPF
{
    public static class ComboBoxExtension
    {
        public static void SetFocus(this ComboBox comboBox)
        {
            if (comboBox == null)
                throw new ArgumentNullException(nameof(comboBox));

            if (comboBox.IsEditable)
            {
                var textBox = (TextBox)comboBox.Template.FindName("PART_EditableTextBox", comboBox);
                if (textBox != null)
                    textBox.Focus();
            }
            else
            {
                comboBox.Focus();
            }
        }
    }
}


// References:
// [Give focus to a ComboBox editable in WPF](https://www.meziantou.net/give-focus-to-a-combobox-editable-in-wpf.htm)
// [WPF setting focus to Combobox](https://stackoverflow.com/questions/20961303/wpf-setting-focus-to-combobox)
// https://stackoverflow.com/questions/817610/wpf-and-initial-focus
// https://stackoverflow.com/questions/2872238/set-the-focus-on-a-textbox-in-xaml-wpf/2872306#2872306
// https://stackoverflow.com/questions/2872238/set-the-focus-on-a-textbox-in-xaml-wpf
