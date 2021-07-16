namespace ShowDialogAsync
{
    using System.Threading.Tasks;
    using System.Windows.Forms;

    public static class DialogExtension
    {
        public static async Task<DialogResult> ShowDialogAsync(this Form form)
        {
            await Task.Yield();

            if (form.IsDisposed)
                return DialogResult.Cancel;

            return form.ShowDialog();
        }
    }
}


// References:
// [Async ShowDialog](https://stackoverflow.com/questions/33406939/async-showdialog)
