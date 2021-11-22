namespace MetafileViewer
{
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    public partial class MetafilePropertiesForm : Form
    {
        public MetafilePropertiesForm(Metafile metafile)
        {
            InitializeComponent();

            propertyGrid_.SelectedObject = metafile;
        }
    }
}
