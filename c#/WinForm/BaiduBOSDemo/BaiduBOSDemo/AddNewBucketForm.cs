namespace BaiduBOSDemo
{
    using Common;

    using MetroFramework.Forms;

    public partial class AddNewBucketForm : MetroForm
    {
        public AddNewBucketForm()
        {
            InitializeComponent();
        }

        public string BucketName
        {
            get;
            private set;
        }

        private void okMetroButton__Click(object sender, System.EventArgs e)
        {
            BucketName = bucketNameMetroTextBox_.Text;
        }

        private void bucketNameMetroTextBox__TextChanged(object sender, System.EventArgs e)
        {
            okMetroButton_.Enabled = !bucketNameMetroTextBox_.Text.IsEmpty();
        }
    }
}
