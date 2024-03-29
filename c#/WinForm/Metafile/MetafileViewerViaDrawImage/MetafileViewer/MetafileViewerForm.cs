﻿namespace MetafileViewer
{
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.IO;
    using System.Windows.Forms;

    using NLog;

    using Common;

    public partial class MetafileViewerForm : Form
    {
        public MetafileViewerForm()
        {
            BackColor = Color.White;

            InitializeComponent();

            AllowDrop = true;
            DragEnter += MetafileViewerForm_DragEnter;
            DragDrop += MetafileViewerForm_DragDrop;
        }

        public MetafileViewerForm(string filePath)
            : this()
        {
            OpenFile(filePath);
        }

        private void MetafileViewerForm_Load(object sender, EventArgs e)
        {
            metafileCanvas_.IsDoubleBuffered = true;

            sizeModeComboBox_.DataSource = Enum.GetValues(typeof(PictureBoxSizeMode));
            sizeModeComboBox_.SelectedItem = PictureBoxSizeMode.Zoom;

            transparentRadioButton_.Checked = true;
            zeroDegreeRadioButton_.Checked = true;
            doubleBufferedCheckBox_.Checked = metafileCanvas_.IsDoubleBuffered;
        }


        private void MetafileViewerForm_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.Copy;
        }

        private void MetafileViewerForm_DragDrop(object sender, DragEventArgs e)
        {
            var files = (string[])e.Data.GetData(DataFormats.FileDrop);
            if (files.Length != 1)
                return;

            if (!File.Exists(files[0]))
                return;

            OpenFile(files[0]);
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
                    OpenFile(openFileDialog.FileName);
            }
        }

        private void exportAsButton__Click(object sender, EventArgs e)
        {
            if (metafileCanvas_.Metafile == null)
                return;

            using (var saveFileDialog = new SaveFileDialog())
            {
                var filters = new string[]
                {
                    "Bitmap Files (*.bmp;*.dib)|*.bmp;*.dib",
                    "JPEG Files (*.jpg;*.jpeg)|*.jpg;*.jpeg",
                    "PNG Files (*.png)|*.png",
                    "Windows Meta Files (*.emf;*.wmf)|*.emf;*.wmf",
                    "All Files (*.*)|*.*",
                };

                saveFileDialog.FileName = Path.GetFileNameWithoutExtension(filePath_);
                saveFileDialog.Filter = string.Join("|", filters);
                saveFileDialog.FilterIndex = 3;

                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    switch (Path.GetExtension(saveFileDialog.FileName).ToLower())
                    {
                        case ".emf":
#if false
                            // TODO:
                            // If orientation is changed, then the exported emf file can not be opened with
                            // this application anymore.
                            metafileCanvas_.Metafile.Save(saveFileDialog.FileName, ImageFormat.Emf);
#else
                            var metafile = metafileCanvas_.Metafile;
                            MetafileUtility.CopyMetafile(ref metafile, saveFileDialog.FileName);
                            metafileCanvas_.Metafile = metafile;
#endif
                            break;
                        case ".wmf":
                            metafile = metafileCanvas_.Metafile;
                            MetafileUtility.MetafileToWMF(ref metafile, saveFileDialog.FileName);
                            metafileCanvas_.Metafile = metafile;
                            break;
                        default:
                            using (var bitmap = MetafileUtility.MetafileToBitmap(metafileCanvas_.Metafile))
                            {
                                bitmap.Save(saveFileDialog.FileName);
                            }
                            break;
                    }
                }
            }
        }

        private void sizeModeComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            metafileCanvas_.SizeMode = (PictureBoxSizeMode)sizeModeComboBox_.SelectedItem;
        }

        private void backgroundRadioButton__CheckedChanged(object sender, EventArgs e)
        {
            var button = sender as RadioButton;

            if (button == null || !button.Checked)
                return;

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
            else
            {
                Debug.Assert(false, "Unexpected background.");
            }
        }

        private void propertiesButton__Click(object sender, EventArgs e)
        {
            using (var propertiesForm = new MetafilePropertiesForm(metafileCanvas_.Metafile))
            {
                propertiesForm.ShowDialog();
                metafileCanvas_.Metafile = propertiesForm.Metafile;
            }
        }

        private void orientationRadioButton__CheckedChanged(object sender, EventArgs e)
        {
            var button = sender as RadioButton;
            if (button == null || !button.Checked)
                return;

            if (button == zeroDegreeRadioButton_)
                metafileCanvas_.Orientation = 0;
            else if (button == ninetyDegreeRadioButton_)
                metafileCanvas_.Orientation = 90;
            else if (button == oneHundredEightyDegreeRadioButton_)
                metafileCanvas_.Orientation = 180;
            else if (button == twoHundredSeventyDegreeRadioButton_)
                metafileCanvas_.Orientation = 270;
            else
                Debug.Assert(false, "Unexpected orientation.");
        }

        private void doubleBufferedCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            metafileCanvas_.IsDoubleBuffered = doubleBufferedCheckBox_.Checked;
        }

        private void OpenFile(string filePath)
        {
            try
            {
                metafileCanvas_.OriginalMetafile = new Metafile(filePath);

                zeroDegreeRadioButton_.Checked = true;

                filePath_ = filePath;

                Text = string.Format("{0} - Metafile Viewer", filePath_);
            }
            catch (Exception ex)
            {
                MsgBox.ErrorFmt("Failed to open metafile {0}.\r\n{1}", filePath, ex.Message);
                Logger.Error(ex, "Failed to open metafile {0}.", filePath);
            }
        }

        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();
        private string filePath_;
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
// [How do I drag and drop files into an application?](https://stackoverflow.com/questions/68598/how-do-i-drag-and-drop-files-into-an-application/89470)
// [Walkthrough: Performing a Drag-and-Drop Operation in Windows Forms](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/walkthrough-performing-a-drag-and-drop-operation-in-windows-forms?view=netframeworkdesktop-4.8)
// [How to drag & drop only one file on form window](https://stackoverflow.com/questions/26752826/how-to-drag-drop-only-one-file-on-form-window)
// [Control.DoDragDrop(Object, DragDropEffects) Method](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.control.dodragdrop?view=windowsdesktop-6.0)
