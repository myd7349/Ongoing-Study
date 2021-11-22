namespace MetafileViewer
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    using Common;

    public partial class MetafileViewerForm : Form
    {
        public MetafileViewerForm()
        {
            BackColor = Color.White;
            InitializeComponent();
        }

        private void MetafileViewerForm_Load(object sender, EventArgs e)
        {
            sizeModeComboBox_.DataSource = Enum.GetValues(typeof(PictureBoxSizeMode));
            sizeModeComboBox_.SelectedItem = PictureBoxSizeMode.Zoom;

            transparentRadioButton_.Checked = true;
        }

        private void openButton__Click(object sender, EventArgs e)
        {
            using (var openFileDialog = new OpenFileDialog())
            {
                var filters = new string[]
                {
                    "Windows Meta Files (*.emf;*.wmf)|*.emf;*.wmf",
                    "All Files (*.*)|*.*",
                };

                openFileDialog.Filter = string.Join("|", filters);

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    metafileCanvas_.Metafile = new Metafile(openFileDialog.FileName);
                }
            }
        }

        private void sizeModeComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            metafileCanvas_.SizeMode = (PictureBoxSizeMode)sizeModeComboBox_.SelectedItem;
        }

        private void transparentRadioButton__CheckedChanged(object sender, EventArgs e)
        {
            var button = sender as RadioButton;

            if (button == transparentRadioButton_)
            {
                metafileCanvas_.SetBackground(8, Color.FromArgb(204, 204, 204));
            }
            else if (button == colorRadioButton_)
            {
                metafileCanvas_.BackgroundImage = null;
                metafileCanvas_.BackColor = Color.White;
                metafileCanvas_.Invalidate();
            }
        }

        private void propertiesButton__Click(object sender, EventArgs e)
        {
            using (var propertiesForm = new MetafilePropertiesForm(metafileCanvas_.Metafile))
            {
                propertiesForm.ShowDialog();
            }
        }
    }
}


// References:
// https://docs.microsoft.com/en-us/dotnet/api/system.drawing.imaging.metafile?view=net-5.0
// [Asynchronous programming with async and await](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/concepts/async/)
// [How to synchronise an asynchronous operation?](https://stackoverflow.com/questions/21173429/how-to-synchronise-an-asynchronous-operation)
// [Non-Generic TaskCompletionSource or alternative](https://stackoverflow.com/questions/11969208/non-generic-taskcompletionsource-or-alternative)
// [C# - asynchronous drawing on a panel](https://stackoverflow.com/questions/53570336/c-sharp-asynchronous-drawing-on-a-panel)
// [How to: Load and Display Metafiles](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/how-to-load-and-display-metafiles?view=netframeworkdesktop-4.8)
// [Binding an enum to a WinForms combo box, and then setting it](https://stackoverflow.com/questions/906899/binding-an-enum-to-a-winforms-combo-box-and-then-setting-it)
