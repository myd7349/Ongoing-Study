namespace MetafileViewer
{
    using System;
    using System.Diagnostics;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    using Vanara.PInvoke;

    using Common;

    public partial class MetafilePropertiesForm : Form
    {
        public MetafilePropertiesForm(Metafile metafile)
        {
            metafile_ = metafile;

            InitializeComponent();

            propertiesComboBox_.Enabled = metafile_ != null;

            if (metafile != null)
                propertiesComboBox_.SelectedIndex = 0;
        }

        public Metafile Metafile
        {
            get
            {
                return metafile_;
            }
        }

        private void propertiesComboBox__SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedItem = propertiesComboBox_.SelectedItem;
            if (selectedItem == null)
                return;

            switch (selectedItem.ToString())
            {
                case "Metafile":
                    propertyGrid_.SelectedObject = metafile_;
                    break;
                case "MetafileHeader":
                    propertyGrid_.SelectedObject = metafile_.GetMetafileHeader();
                    break;
                case "ENHMETAHEADER":
                    using (var metafile = MetafileUtility.CopyMetafile(ref metafile_))
                    {
                        // Metafile.GetHenhmetafile is just a wrapper of GdipGetHemfFromMetafile:
                        // https://github.com/dotnet/runtime/blob/78c6505cffe2558b036fbe44cd27038affbb6cce/src/libraries/System.Drawing.Common/src/System/Drawing/Imaging/Metafile.Windows.cs#L379-L383
                        // and according to:
                        // http://www.jose.it-berater.org/gdiplus/reference/flatapi/graphics/gdipgethemffrommetafile.htm
                        // > GdipGetHemfFromMetafile:
                        // > This method sets the Metafile object to an invalid state. The user is responsible for calling DeleteEnhMetafile,
                        // > to delete the Windows handle.
                        var enhMetafileHandle = metafile.GetHenhmetafile();
                        if (enhMetafileHandle != IntPtr.Zero)
                        {
                            var header = Gdi32.GetEnhMetaFileHeader(enhMetafileHandle);
                            propertyGrid_.SelectedObject = new EnhMetaHeader(header);

                            Gdi32.DeleteEnhMetaFile(enhMetafileHandle);
                        }
                    }
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
        }

        private Metafile metafile_;
    }
}


// References:
// [Modifying structure property in a PropertyGrid](https://stackoverflow.com/questions/15746897/modifying-structure-property-in-a-propertygrid)
