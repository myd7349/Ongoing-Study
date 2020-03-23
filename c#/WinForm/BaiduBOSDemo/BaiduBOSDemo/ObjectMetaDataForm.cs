namespace BaiduBOSDemo
{
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using BaiduBce.Services.Bos;

    using MetroFramework.Forms;

    public partial class ObjectMetaDataForm : MetroForm
    {
        public ObjectMetaDataForm(BosClient bosClient, string bucketName, string objectKey)
        {
            bosClient_ = bosClient;
            bucket_ = bucketName;
            objectKey_ = objectKey;

            InitializeComponent();
        }

        private async void ObjectMetaDataForm_Load(object sender, System.EventArgs e)
        {
            try
            {
                objectPropertyGrid_.SelectedObject = await Task.Run(() => bosClient_.GetObjectMetadata(bucket_, objectKey_));
            }
            catch (Exception ex)
            {

                MessageBox.Show(
                    this,
                    "Failed to get object metadata:\n" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        private void generateUrlMetroButton__Click(object sender, System.EventArgs e)
        {
            var secondsString = expirationInSecondsMetroTextBox_.Text;
            int seconds;
            if (!int.TryParse(secondsString, out seconds) || seconds < -1)
                seconds = 1800;

            var uri = bosClient_.GeneratePresignedUrl(bucket_, objectKey_, seconds);
            urlMetroTextBox_.Text = uri.ToString();

            try
            {
                Clipboard.SetDataObject(urlMetroTextBox_.Text, true);
                MessageBox.Show(
                    this,
                    "The generated URL has been copied to the clipboard.",
                    "Information:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this,
                    "Failed to copy the generated URL to the clipboard:\n" +
                    ex.ToString() +
                    "\nYou may copy it manually.",
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        private BosClient bosClient_;
        private string bucket_;
        private string objectKey_;
    }
}


// References:
// https://stackoverflow.com/questions/463299/how-do-i-make-a-textbox-that-only-accepts-numbers
