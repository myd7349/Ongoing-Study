namespace MetafileViewer
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.IO;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

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

        private void MetafileViewerForm_Load(object sender, System.EventArgs e)
        {

        }

        private void MetafileViewerForm_Layout(object sender, LayoutEventArgs e)
        {

        }

        private void MetafileViewerForm_Resize(object sender, System.EventArgs e)
        {

        }

        private void MetafileViewerForm_Paint(object sender, PaintEventArgs e)
        {
            Render(e.Graphics);
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

            Metafile metafile;
            try
            {
                metafile = new Metafile(files[0]);
            }
            catch (Exception ex)
            {
                MsgBox.Error("Failed to open metafile {0}.\r\n{1}", files[0], ex.Message);
                return;
            }

            metafile_ = metafile;
            pictureBox_.Image = metafile_;
        }

        private void openButton__Click(object sender, System.EventArgs e)
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
                    if (metafile_ != null)
                        metafile_.Dispose();

                    metafile_ = new Metafile(openFileDialog.FileName);
                    pictureBox_.Image = metafile_;
                }
            }
        }

        private void Render(Graphics graphics)
        {
            if (metafile_ != null)
            {
                graphics.ScaleTransform(0.2f, 0.2f);
                //graphics.TranslateTransform(metafile_.Height / 2, 0F);
                //graphics.RotateTransform(45F);
                graphics.EnumerateMetafile(metafile_, Point.Empty, MetafileCallback);
            }
        }

        private bool MetafileCallback(EmfPlusRecordType recordType, int flags,
            int dataSize, IntPtr data, PlayRecordCallback callbackData)
        {
            byte[] dataArray = null;
            if (data != IntPtr.Zero)
            {
                // Copy the unmanaged record to a managed byte buffer 
                // that can be used by PlayRecord.
                dataArray = new byte[dataSize];
                Marshal.Copy(data, dataArray, 0, dataSize);
            }

            metafile_.PlayRecord(recordType, flags, dataSize, dataArray);

            return true;
        }

        private Metafile metafile_;
    }
}


// References:
// https://docs.microsoft.com/en-us/dotnet/api/system.drawing.imaging.metafile?view=net-5.0
// [Asynchronous programming with async and await](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/concepts/async/)
// [How to synchronise an asynchronous operation?](https://stackoverflow.com/questions/21173429/how-to-synchronise-an-asynchronous-operation)
// [Non-Generic TaskCompletionSource or alternative](https://stackoverflow.com/questions/11969208/non-generic-taskcompletionsource-or-alternative)
// [C# - asynchronous drawing on a panel](https://stackoverflow.com/questions/53570336/c-sharp-asynchronous-drawing-on-a-panel)
// [How to: Load and Display Metafiles](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/how-to-load-and-display-metafiles?view=netframeworkdesktop-4.8)
// [PlayEnhMetaFile function (wingdi.h)](https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-playenhmetafile)
// [Opening an Enhanced Metafile and Displaying Its Contents](https://docs.microsoft.com/en-us/windows/win32/gdi/opening-an-enhanced-metafile-and-displaying-its-contents)
// [How do I drag and drop files into an application?](https://stackoverflow.com/questions/68598/how-do-i-drag-and-drop-files-into-an-application/89470)
// [Walkthrough: Performing a Drag-and-Drop Operation in Windows Forms](https://docs.microsoft.com/en-us/dotnet/desktop/winforms/advanced/walkthrough-performing-a-drag-and-drop-operation-in-windows-forms?view=netframeworkdesktop-4.8)
// [How to drag & drop only one file on form window](https://stackoverflow.com/questions/26752826/how-to-drag-drop-only-one-file-on-form-window)
// [Control.DoDragDrop(Object, DragDropEffects) Method](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.control.dodragdrop?view=windowsdesktop-6.0)
