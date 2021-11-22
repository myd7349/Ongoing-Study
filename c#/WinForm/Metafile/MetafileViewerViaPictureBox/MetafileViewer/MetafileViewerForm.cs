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

            pictureBox_.SetBackground(8, Color.FromArgb(204, 204, 204));
            pictureBox_.SizeMode = PictureBoxSizeMode.Zoom;
            pictureBox_.WaitOnLoad = false;
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
#if false
                    Metafile metafile = new Metafile(openFileDialog.FileName);
                    pictureBox_.Image = metafile;
#else
                    pictureBox_.LoadAsync(openFileDialog.FileName);
                    pictureBox_.LoadCompleted += PictureBox__LoadCompleted;
#endif
                }
            }
        }

        private void PictureBox__LoadCompleted(object sender, System.ComponentModel.AsyncCompletedEventArgs e)
        {
            propertiesButton_.Enabled = true;
        }

        private void propertiesButton__Click(object sender, EventArgs e)
        {
            Metafile metafile = pictureBox_.Image as Metafile;
            using (var propertiesForm = new MetafilePropertiesForm(metafile))
            {
                propertiesForm.ShowDialog();
            }
        }
    }
}


// References:
// [How to: Load and Display Metafiles](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/how-to-load-and-display-metafiles?view=netframeworkdesktop-4.8)
// [PictureBox Class](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.picturebox?view=windowsdesktop-5.0)
