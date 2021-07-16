namespace MetafileViewer
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.Runtime.InteropServices;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    public partial class MetafileViewerForm : Form
    {
        public MetafileViewerForm()
        {
            BackColor = Color.White;

            InitializeComponent();
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
                    Invalidate();
                }
            }
        }
    }

    public partial class MetafileViewerForm : Form
    {
        private void Render(Graphics graphics)
        {
            if (metafile_ != null)
            {
                //graphics.TranslateTransform(metafile_.Height, 0F);
                graphics.RotateTransform(45F);
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
