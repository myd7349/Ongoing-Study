namespace BaiduBOSDemo
{
    using System;
    using System.Data;
    using System.Diagnostics;
    using System.Drawing;
    using System.IO;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using BaiduBce;
    using BaiduBce.Services.Bos;

    using FastMember;

    using MetroFramework.Forms;

    public partial class BaiduBOSForm : MetroForm
    {
        public BaiduBOSForm()
        {
            InitializeComponent();

            bucketTabControl_.TabPageAdding += BucketTabControl__AddNewBucket;
            bucketTabControl_.TabPageDeleting += BucketTabControl__DeleteBucket;
        }

        private void BaiduBOSForm_Load(object sender, EventArgs e)
        {
            settings_ = Settings.Load();

            if (string.IsNullOrEmpty(settings_.AccessKey) ||
                string.IsNullOrEmpty(settings_.SecretAccessKey) ||
                string.IsNullOrEmpty(settings_.EndPoint))
            {
                settingsToolStripButton__Click(this, null);
            }
            else
            {
                CurrentBucket_ = settings_.CurrentBucket;

                CreateBosClient();
                UpdateBucketList();
            }
        }

        private void BaiduBOSForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Settings.Store(settings_);
        }

        private void settingsToolStripButton__Click(object sender, EventArgs e)
        {
            using (var settingsForm = new SettingsForm(settings_))
            {
                settingsForm.ShowDialog();
                settings_ = settingsForm.Settings;
                CreateBosClient();
                UpdateBucketList();
            }
        }

        private void objectFilterToolStripTextBox__TextChanged(object sender, EventArgs e)
        {
            UpdateObjectList();
        }

        private bool BucketTabControl__AddNewBucket(object sender, Common.WinForms.TabPageEventArgs e)
        {
            using (var addNewBucketForm = new AddNewBucketForm())
            {
                if (addNewBucketForm.ShowDialog(this) == DialogResult.OK)
                {
                    try
                    {
                        bosClient_.CreateBucket(addNewBucketForm.BucketName);
                        e.TabPage.Text = addNewBucketForm.BucketName;
                        return true;
                    }
                    catch (BceServiceException ex)
                    {
                        MessageBox.Show(
                            this,
                            "Failed to create bucket \"" +
                            addNewBucketForm.BucketName +
                            "\":\n" +
                            ex.Message,
                            "Error:",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                        return false;
                    }
                }
            }

            return false;
        }

        private bool BucketTabControl__DeleteBucket(object sender, Common.WinForms.TabPageEventArgs e)
        {
            var tabPage = e.TabPage;

            if (bosClient_.DoesBucketExist(tabPage.Text))
            {
                if (MessageBox.Show(
                    this,
                    "Do you really want to delete bucket \"" +
                    tabPage.Text +
                    "\"?",
                    "Question:",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Question,
                    MessageBoxDefaultButton.Button2) == DialogResult.Yes)
                {
                    try
                    {
                        bosClient_.DeleteBucket(tabPage.Text);
                        return true;
                    }
                    catch (BceServiceException ex)
                    {
                        MessageBox.Show(
                            this,
                            "Failed to delete bucket \"" +
                            tabPage.Text +
                            "\":\n" +
                            ex.Message,
                            "Error:",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                        return false;
                    }
                }
            }
            else
            {
                MessageBox.Show(
                    this,
                    "Bucket \"" +
                    tabPage.Text +
                    "\" doesn't exist.",
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }

            return false;
        }

        private async void uploadToolStripButton__Click(object sender, EventArgs e)
        {
            string filePath;

            using (var openFileDialog = new OpenFileDialog())
            {
                var filters = new string[]
                {
                    "All Files (*.*)|*.*",
                };

                openFileDialog.Filter = string.Join("|", filters);
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                    filePath = openFileDialog.FileName;
                else
                    return;
            }

            toolStripProgressBar_.Value = 0;
            uploadToolStripButton_.Enabled = false;
            settingsToolStripButton_.Enabled = false;

            toolStripProgressBar_.Visible = true;
            pauseToolStripButton_.Visible = true;
            abortToolStripButton_.Visible = true;

            var objectKey = settings_.UseFileFullPathAsObjectKey ? filePath : Path.GetFileName(filePath);

            pauseCancellationTokenSource_ = new CancellationTokenSource();
            abortCancellationTokenSource_ = new CancellationTokenSource();

            BOSMultipartUploadRequestInfo bosMultipartUploadRequestInfo;

            var multipartUploadInfoFile = filePath + BOSMultipartUploadRequestInfo.UploadRequestInfoFileExtension;
            if (File.Exists(multipartUploadInfoFile))
            {
                bosMultipartUploadRequestInfo = JsonHelper.Load<BOSMultipartUploadRequestInfo>(multipartUploadInfoFile);
            }
            else
            {
                bosMultipartUploadRequestInfo = new BOSMultipartUploadRequestInfo
                {
                    FilePath = filePath,
                    Bucket = CurrentBucket_,
                    ObjectKey = objectKey,
                    PartSize = 1024 * 1024 * 5,
                };
            }

            var bosMultipartUploadRequest = new BOSMultipartUploadRequest
            {
                RequestInfo = bosMultipartUploadRequestInfo,
                PauseCancellationToken = pauseCancellationTokenSource_.Token,
                AbortCancellationToken = abortCancellationTokenSource_.Token,
            };

            bool ok = false;
            try
            {
                ok = await bosClient_.UploadFileAsync(filePath, bosMultipartUploadRequest,
                    new ProgressBarReporter(toolStripProgressBar_.ProgressBar, SynchronizationContext.Current));
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this,
                    "Failed to upload objects:\n" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }

            if (ok)
            {
                UpdateObjectList();

                if (File.Exists(multipartUploadInfoFile))
                    File.Delete(multipartUploadInfoFile);
            }
            else if (pauseCancellationTokenSource_.IsCancellationRequested)
            {
                JsonHelper.Store(multipartUploadInfoFile, bosMultipartUploadRequestInfo);
            }

            uploadToolStripButton_.Enabled = true;
            settingsToolStripButton_.Enabled = true;

            toolStripProgressBar_.Visible = false;
            pauseToolStripButton_.Visible = false;
            abortToolStripButton_.Visible = false;

            pauseCancellationTokenSource_ = null;
            abortCancellationTokenSource_ = null;
        }

        private void downloadToolStripButton__Click(object sender, EventArgs e)
        {
            var objectListView = bucketTabControl_.SelectedTab.Controls[0] as BOSObjectListView;
            Debug.Assert(objectListView != null);
        }

        private async void deleteToolStripButton__Click(object sender, EventArgs e)
        {
            var objectListView = bucketTabControl_.SelectedTab.Controls[0] as BOSObjectListView;
            Debug.Assert(objectListView != null);
            Debug.Assert(objectListView.SelectedItems.Count > 0);

            var objectNames = objectListView.SelectedItems
                .Cast<ListViewItem>()
                .Select(item => item.SubItems[0].Text)
                .ToArray();
            var answer = MessageBox.Show(
                this,
                "The following objects will be deleted:\n" +
                string.Join("\n", objectNames),
                "Confirm:",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question,
                MessageBoxDefaultButton.Button2
                );
            if (answer == DialogResult.No)
                return;

            try
            {
                await bosClient_.DeleteObjectsAsync(CurrentBucket_, objectNames);
                UpdateObjectList();
            }
            catch (BceServiceException ex)
            {
                MessageBox.Show(
                    this,
                    "Failed to delete objects:\n" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        private void refreshToolStripButton__Click(object sender, EventArgs e)
        {
            UpdateBucketList();
        }

        private async void propertiesToolStripButton__Click(object sender, EventArgs e)
        {
            var objectListView = bucketTabControl_.SelectedTab.Controls[0] as BOSObjectListView;
            Debug.Assert(objectListView != null);
            Debug.Assert(objectListView.SelectedItems.Count == 1);

            var objectKey = objectListView.SelectedItems
                .Cast<ListViewItem>()
                .Select(item => item.SubItems[0].Text)
                .First();

            try
            {
                var objectMetadata = await Task.Run(() => bosClient_.GetObjectMetadata(CurrentBucket_, objectKey));
                using (var objectMetaDataForm = new ObjectMetaDataForm(objectMetadata))
                {
                    objectMetaDataForm.ShowDialog();
                }
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

        private void pauseToolStripButton__Click(object sender, EventArgs e)
        {
            Debug.Assert(pauseCancellationTokenSource_ != null);
            pauseCancellationTokenSource_.Cancel();
        }

        private void abortToolStripButton__Click(object sender, EventArgs e)
        {
            Debug.Assert(abortCancellationTokenSource_ != null);
            abortCancellationTokenSource_.Cancel();
        }

        private void bucketTabControl__Selected(object sender, TabControlEventArgs e)
        {
            CurrentBucket_ = bucketTabControl_.SelectedTab.Text;

            UpdateObjectList();
        }

        private void ObjectListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            var objectListView = sender as BOSObjectListView;
            Debug.Assert(objectListView != null);

            downloadToolStripButton_.Enabled = objectListView.SelectedItems.Count > 0;
            deleteToolStripButton_.Enabled = objectListView.SelectedItems.Count > 0;
            propertiesToolStripButton_.Enabled = objectListView.SelectedItems.Count == 1;
        }

        private void CreateBosClient()
        {
            try
            {
                bosClient_ = BOSHelper.CreateBosClient(settings_);
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this,
                    "Invalid settings!\n" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);

                //BeginInvoke(new MethodInvoker(Close));
            }
        }

        private async void UpdateBucketList()
        {
            uploadToolStripButton_.Enabled = false;

            var currentBucket = CurrentBucket_;
            bucketTabControl_.TabPages.Clear(); // This will cause CurrentBucket_ be changed.
            CurrentBucket_ = currentBucket;

            if (bosClient_ == null)
                return;

            try
            {
                var buckets = (await bosClient_.GetBucketsAsync()).ToArray();

                bucketTabControl_.TabPages.AddRange(buckets.Select(bucketName => new TabPage(bucketName) { Name = bucketName }).ToArray());
                bucketTabControl_.TabPages.Add("+");

                if (buckets.Length > 0)
                {
                    int index = bucketTabControl_.TabPages.IndexOfKey(CurrentBucket_);
                    if (index == -1)
                        index = 0;

                    if (index == 0)
                        bucketTabControl__Selected(this, null);
                    else
                        bucketTabControl_.SelectedIndex = index;

                    uploadToolStripButton_.Enabled = true;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this,
                    "Failed to get bucket list:" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        private async void UpdateObjectList()
        {
            var tabPage = bucketTabControl_.SelectedTab;
            BOSObjectListView objectListView;
            if (tabPage.Controls.Count == 0)
            {
                objectListView = new BOSObjectListView();
                objectListView.Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Bottom;
                objectListView.Bounds = new Rectangle(4, 4, tabPage.Width - 8, tabPage.Height - 8);
                objectListView.SelectedIndexChanged += ObjectListView_SelectedIndexChanged;

                tabPage.Controls.Add(objectListView);
            }
            else
            {
                objectListView = tabPage.Controls[0] as BOSObjectListView;
            }

            try
            {
                objectListView.DataSource = await CreateObjectDataTable();
            }
            catch (Exception)
            {
            }

            objectListView.AutoResizeColumns();
            objectListView.SelectedItems.Clear();

            downloadToolStripButton_.Enabled = objectListView.SelectedItems.Count > 0;
            deleteToolStripButton_.Enabled = objectListView.SelectedItems.Count > 0;
            propertiesToolStripButton_.Enabled = objectListView.SelectedItems.Count == 1;

            totalObjectsNumbertoolStripStatusLabel_.Text = objectListView.Items.Count.ToString();
        }

        private Task<DataTable> CreateObjectDataTable()
        {
            return Task.Run(
                async () =>
                {
                    var objects = await bosClient_.GetObjectsAsync(
                        CurrentBucket_,
                        objectFilterToolStripTextBox_.Text,
                        delimiterToolStripTextBox_.Text);
                    if (objects == null)
                        return null;

                    var dataTable = new DataTable();
                    using (var reader = ObjectReader.Create(objects, "Key", "ETag", "Size", "LastModified"))
                    {
                        dataTable.Load(reader);
                    }

                    return dataTable;
                });
        }

        private string CurrentBucket_
        {
            get
            {
                return settings_.CurrentBucket;
            }
            set
            {
                settings_.CurrentBucket = value;
            }
        }

        private Settings settings_;
        private BosClient bosClient_;
        private CancellationTokenSource pauseCancellationTokenSource_;
        private CancellationTokenSource abortCancellationTokenSource_;
    }
}

// References:
// Icons: open_icon_library-standard-0.11
// https://stackoverflow.com/questions/1189728/why-cant-i-use-linq-on-listview-selecteditems
// https://stackoverflow.com/questions/5383310/catch-an-exception-thrown-by-an-async-void-method
// https://stackoverflow.com/questions/3529928/how-do-i-put-text-on-progressbar
// https://github.com/ukushu/TextProgressBar
// https://stackoverflow.com/questions/32067034/how-to-handle-task-run-exception
// https://stackoverflow.com/questions/731068/closing-a-form-from-the-load-handler
