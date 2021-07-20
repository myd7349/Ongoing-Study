namespace ModelessForm
{
    using System.Windows.Forms;

    public partial class ModelessForm : Form
    {
        public ModelessForm()
        {
            InitializeComponent();
        }

        private void ModelessForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
                Hide();
            }
        }

        private void okButton__Click(object sender, System.EventArgs e)
        {
            Close();
        }

        private void cancelButton__Click(object sender, System.EventArgs e)
        {
            Close();
        }
    }
}


// References:
// [How to create a modeless dialog box within a C# console app](https://stackoverflow.com/questions/38549753/how-to-create-a-modeless-dialog-box-within-a-c-sharp-console-app)
// [Preventing a dialog from closing in the button's click event handler](https://stackoverflow.com/questions/2499644/preventing-a-dialog-from-closing-in-the-buttons-click-event-handler)
