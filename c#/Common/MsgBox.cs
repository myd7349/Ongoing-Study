namespace Common
{
    using System.Windows.Forms;

    public static class MsgBox
    {
        public static DialogResult Information(string format, params object[] args)
        {
            return Information(string.Format(format, args));
        }

        public static DialogResult Information(string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(text, caption, buttons, MessageBoxIcon.Information);
        }

        public static DialogResult Information(IWin32Window owner, string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(owner, text, caption, buttons, MessageBoxIcon.Information);
        }

        public static DialogResult Question(string format, params object[] args)
        {
            return Question(string.Format(format, args));
        }

        public static DialogResult Question(string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(text, caption, buttons, MessageBoxIcon.Question);
        }

        public static DialogResult Question(IWin32Window owner, string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(owner, text, caption, buttons, MessageBoxIcon.Question);
        }

        public static DialogResult Warning(string format, params object[] args)
        {
            return Warning(string.Format(format, args));
        }

        public static DialogResult Warning(string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(text, caption, buttons, MessageBoxIcon.Warning);
        }

        public static DialogResult Warning(IWin32Window owner, string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(owner, text, caption, buttons, MessageBoxIcon.Warning);
        }

        public static DialogResult Error(string format, params object[] args)
        {
            return Error(string.Format(format, args));
        }

        public static DialogResult Error(string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(text, caption, buttons, MessageBoxIcon.Error);
        }

        public static DialogResult Error(IWin32Window owner, string text, string caption = "", MessageBoxButtons buttons = MessageBoxButtons.OK)
        {
            return MessageBox.Show(owner, text, caption, buttons, MessageBoxIcon.Error);
        }
    }
}


// References:
// https://github.com/dotnet/winforms/blob/main/src/System.Windows.Forms/src/System/Windows/Forms/MessageBox.cs
