namespace MetafileViewer
{
    using System;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    using Vanara.PInvoke;

    public partial class MetafilePropertiesForm : Form
    {
        public MetafilePropertiesForm(MetafileProxy metafile)
        {
            metafileProxy_ = metafile;

            InitializeComponent();

            propertyGrid_.SelectedObject = metafile?.Metafile;
            useGdi32CheckBox_.Enabled = metafileProxy_?.Metafile != null;
        }

        private void useGdi32CheckBox__CheckedChanged(object sender, EventArgs e)
        {
            if (useGdi32CheckBox_.Checked)
            {
                var enhMetafileHandle = metafileProxy_.Metafile.GetHenhmetafile();
                if (enhMetafileHandle != IntPtr.Zero)
                {
                    var header = Gdi32.GetEnhMetaFileHeader(enhMetafileHandle);
                    propertyGrid_.SelectedObject = new EnhMetaHeader(header);

                    //Gdi32.DeleteEnhMetaFile(enhMetafileHandle);

                    // It seems that GetHenhmetafile will cause the
                    // original Metafile object invalid.
                    metafileProxy_.Metafile = new Metafile(enhMetafileHandle, true);
                }
            }
            else
            {
                propertyGrid_.SelectedObject = metafileProxy_.Metafile;
            }
        }

        private MetafileProxy metafileProxy_;
    }
}


// References:
// [Modifying structure property in a PropertyGrid](https://stackoverflow.com/questions/15746897/modifying-structure-property-in-a-propertygrid)
