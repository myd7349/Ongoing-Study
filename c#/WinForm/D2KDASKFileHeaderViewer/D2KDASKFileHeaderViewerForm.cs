namespace D2KDASKFileHeaderViewer
{
    using System;
    using System.IO;
    using System.Runtime.InteropServices;
    using System.Windows.Forms;

    using Common;

    public partial class D2KDASKFileHeaderViewerForm : Form
    {
        public D2KDASKFileHeaderViewerForm()
        {
            InitializeComponent();

            propertyGrid.PropertySort = PropertySort.NoSort;
        }

        private void openFileButton_Click(object sender, EventArgs e)
        {
            using (var openFileDialog = new OpenFileDialog())
            {
                var filters = new string[] {
                    "D2K-DASK Log Files|*.dat;*.daq",
                };

                openFileDialog.Filter = string.Join("|", filters);

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    fileNameLabel.Text = openFileDialog.FileName;

                    using (var stream = File.OpenRead(openFileDialog.FileName))
                    using (var reader = new BinaryReader(stream))
                    {
                        var headerSize = Marshal.SizeOf<D2KDASKFileHeader>();
                        if (stream.Length > headerSize)
                        {
                            var header = StructHelpers.BytesToStruct<D2KDASKFileHeader>(reader.ReadBytes(headerSize));
                            propertyGrid.SelectedObject = new D2KDASKFileHeaderWrapper(header);
                        }
                    }
                }
            }
        }
    }
}

// References:
// https://stackoverflow.com/questions/5962595/how-do-you-resize-a-form-to-fit-its-content-automatically

