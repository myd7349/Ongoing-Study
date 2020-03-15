namespace BaiduBOSDemo
{
    using System;
    using System.Data;
    using System.IO;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using BaiduBce;
    using BaiduBce.Auth;
    using BaiduBce.Services.Bos;

    using FastMember;

    public partial class BaiduBOSForm : Form
    {
        public BaiduBOSForm()
        {
            InitializeComponent();
        }

        private void BaiduBOSForm_Load(object sender, EventArgs e)
        {
            var settings = Settings.Load();

            bosClient_ = CreateBosClient(settings);

            currentBucket_ = settings.CurrentBucket;

            var buckets = bosClient_.GetBuckets();
            bucketComboBox_.Items.AddRange(buckets.ToArray());

            if (buckets.Contains(currentBucket_))
                bucketComboBox_.SelectedIndex = bucketComboBox_.Items.IndexOf(currentBucket_);
            else
                bucketComboBox_.SelectedIndex = 0;

            uploadButton_.Enabled = false;
        }

        private void BaiduBOSForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            var settings = Settings.Load();
            settings.CurrentBucket = currentBucket_;
            Settings.Store(settings);
        }

        private void settingsButton_Click(object sender, EventArgs e)
        {
            using (var settingsForm = new SettingsForm())
            {
                settingsForm.ShowDialog(this);
                bosClient_ = CreateBosClient(Settings.Load());
            }
        }

        private void bucketComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentBucket_ = bucketComboBox_.SelectedItem.ToString();

            UpdateObjectList();
        }

        private void selectFileButton_Click(object sender, EventArgs e)
        {
            using (var openFileDialog = new OpenFileDialog())
            {
                var filters = new string[]
                {
                    "All Files (*.*)|*.*",
                };

                openFileDialog.Filter = string.Join("|", filters);
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    filePathTextBox_.Text = openFileDialog.FileName;
                    uploadButton_.Enabled = true;
                }
            }
        }

        private async void uploadButton_Click(object sender, EventArgs e)
        {
            if (cancellationTokenSource_ == null)
            {
                selectFileButton_.Enabled = false;
                uploadButton_.Text = "Pause";

                var filePath = filePathTextBox_.Text;

                cancellationTokenSource_ = new CancellationTokenSource();
                bool ok = await bosClient_.UploadFileAsync(
                    currentBucket_,
                    Path.GetFileName(filePath),
                    filePath,
                    cancellationTokenSource_.Token,
                    new ProgressBarReporter(transmissionProgressBar_, SynchronizationContext.Current)
                    );

                if (ok)
                    UpdateObjectList();

                selectFileButton_.Enabled = true;
                uploadButton_.Text = "Upload";
            }
            else
            {
                cancellationTokenSource_.Cancel();
                cancellationTokenSource_ = null;
            }
        }

        private static BosClient CreateBosClient(Settings settings)
        {
            BceClientConfiguration clientConfig = new BceClientConfiguration();
            clientConfig.Credentials = new DefaultBceCredentials(settings.AccessKey, settings.SecretAccessKey);
            clientConfig.Endpoint = settings.EndPoint;

            return new BosClient(clientConfig);
        }

        private void UpdateObjectList()
        {
            var objects = bosClient_.GetObjects(currentBucket_);
            if (objects == null)
                return;

            var dataTable = new DataTable();
            using (var reader = ObjectReader.Create(objects, "Key", "ETag", "Size", "LastModified"))
            {
                dataTable.Load(reader);
            }

            objectDataGridView_.DataSource = dataTable;
            objectDataGridView_.AutoResizeToFitContent();
        }

        private BosClient bosClient_;
        private string currentBucket_;
        private CancellationTokenSource cancellationTokenSource_;
    }
}
