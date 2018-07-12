namespace Common
{
    using System.Diagnostics;
    using System.Windows.Forms;

    public static class FormExtensions
    {
        public static DialogResult ShowDialogEx(this Form form, Control owner)
        {
            Debug.Assert(form != null && owner != null);

            form.ShowInTaskbar = false;
            return form.ShowDialog(owner);
        }
    }
}


// References:
// https://stackoverflow.com/questions/14045722/showdialog-not-showing-the-form-on-top-of-the-main-form#
// https://stackoverflow.com/questions/816885/form-showdialog-or-form-showdialogthis
// https://stackoverflow.com/questions/10982523/wpf-modal-window-as-tool-window-in-winforms-disappears
// https://www.mgenware.com/blog/?p=1935
