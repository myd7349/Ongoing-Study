namespace BaiduBOSDemo
{
    using BaiduBce.Services.Bos.Model;

    using MetroFramework.Forms;

    public partial class ObjectMetaDataForm : MetroForm
    {
        public ObjectMetaDataForm(ObjectMetadata objectMetaData)
        {
            InitializeComponent();

            objectPropertyGrid_.SelectedObject = objectMetaData;
        }
    }
}
