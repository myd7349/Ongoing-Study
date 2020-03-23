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
                CreateBosClient();
                UpdateBucketList();
            }
        }

        private void BaiduBOSForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (abortCancellationTokenSource_ != null)
            {
#if false
                var reply = MessageBox.Show(
                    this,
                    "There are still some unfinished transfer tasks.\nDo you want to abort them and exit?",
                    "Warning:",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning,
                    MessageBoxDefaultButton.Button2);
                if (reply == DialogResult.Yes)
                    e.Cancel = true;
#else
                MessageBox.Show(
                    this,
                    "There are still some unfinished transfer tasks.\nIf you want to exit, please abort/cancel them first.",
                    "Warning:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Warning);
                e.Cancel = true;
#endif
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
            downloadToolStripButton_.Enabled = false;
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
                    PartSize = settings_.UploadPartSize > 0 ? settings_.UploadPartSize : 1024 * 1024 * 1,
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
                ok = await bosClient_.UploadFileAsync(bosMultipartUploadRequest,
                    new ProgressBarReporter(toolStripProgressBar_.ProgressBar, SynchronizationContext.Current));
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this,
                    "Failed to upload object:\n" + ex.Message,
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
            downloadToolStripButton_.Enabled = true;
            settingsToolStripButton_.Enabled = true;

            toolStripProgressBar_.Visible = false;
            pauseToolStripButton_.Visible = false;
            abortToolStripButton_.Visible = false;

            pauseCancellationTokenSource_ = null;
            abortCancellationTokenSource_ = null;
        }

        private async void downloadToolStripButton__Click(object sender, EventArgs e)
        {
            var objectTable = bucketTabControl_.SelectedTab.Controls[0] as BOSObjectTable;
            Debug.Assert(objectTable != null);

            var objectKey = objectTable.SelectedItems[0].Cells[0].Text;

            string filePath;
            using (var saveFileDialog = new SaveFileDialog())
            {
                var filters = new string[]
                {
                    "All Files (*.*)|*.*",
                };

                saveFileDialog.FileName = Path.GetFileName(objectKey);
                saveFileDialog.Filter = string.Join("|", filters);
                saveFileDialog.OverwritePrompt = true;
                saveFileDialog.CheckPathExists = true;
                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                    filePath = saveFileDialog.FileName;
                else
                    return;
            }
            
            toolStripProgressBar_.Value = 0;
            uploadToolStripButton_.Enabled = false;
            downloadToolStripButton_.Enabled = false;
            settingsToolStripButton_.Enabled = false;

            toolStripProgressBar_.Visible = true;
            pauseToolStripButton_.Visible = true;
            abortToolStripButton_.Visible = true;

            pauseCancellationTokenSource_ = new CancellationTokenSource();
            abortCancellationTokenSource_ = new CancellationTokenSource();

            
            BOSDownloadRequestInfo bosDownloadRequestInfo;

            var downloadInfoFile = filePath + BOSDownloadRequestInfo.DownloadRequestInfoFileExtension;
            var downloadingFilePath = filePath + BOSDownloadRequestInfo.DownloadingFileExtension;
            if (File.Exists(downloadInfoFile))
            {
                bosDownloadRequestInfo = JsonHelper.Load<BOSDownloadRequestInfo>(downloadInfoFile);
            }
            else
            {
                bosDownloadRequestInfo = new BOSDownloadRequestInfo
                {
                    FilePath = downloadingFilePath,
                    Bucket = CurrentBucket_,
                    ObjectKey = objectKey,
                    DownloadSize = settings_.DownloadSize > 0 ? settings_.DownloadSize : 1024 * 256,
                };
            }

            var bosDownloadRequest = new BOSDownloadRequest
            {
                RequestInfo = bosDownloadRequestInfo,
                PauseCancellationToken = pauseCancellationTokenSource_.Token,
                AbortCancellationToken = abortCancellationTokenSource_.Token,
            };
            
            bool ok = false;
            try
            {
                ok = await bosClient_.DownloadFileAsync(bosDownloadRequest,
                    new ProgressBarReporter(toolStripProgressBar_.ProgressBar, SynchronizationContext.Current));
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this,
                    "Failed to download object:\n" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }

            if (ok)
            {
                if (File.Exists(filePath))
                    File.Delete(filePath);

                if (File.Exists(downloadingFilePath))
                    File.Move(downloadingFilePath, filePath);

                if (File.Exists(downloadInfoFile))
                    File.Delete(downloadInfoFile);
            }
            else if (pauseCancellationTokenSource_.IsCancellationRequested)
            {
                JsonHelper.Store(downloadInfoFile, bosDownloadRequestInfo);
            }
            else if (abortCancellationTokenSource_.IsCancellationRequested)
            {
                if (File.Exists(downloadingFilePath))
                    File.Delete(downloadingFilePath);
            }

            uploadToolStripButton_.Enabled = true;
            downloadToolStripButton_.Enabled = true;
            settingsToolStripButton_.Enabled = true;

            toolStripProgressBar_.Visible = false;
            pauseToolStripButton_.Visible = false;
            abortToolStripButton_.Visible = false;

            pauseCancellationTokenSource_ = null;
            abortCancellationTokenSource_ = null;
        }

        private async void deleteToolStripButton__Click(object sender, EventArgs e)
        {
            var objectTable = bucketTabControl_.SelectedTab.Controls[0] as BOSObjectTable;
            Debug.Assert(objectTable != null);
            Debug.Assert(objectTable.SelectedItems.Length > 0);

            var objectNames = objectTable.SelectedItems
                .Select(item => item.Cells[0].Text)
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

        private void propertiesToolStripButton__Click(object sender, EventArgs e)
        {
            var objectTable = bucketTabControl_.SelectedTab.Controls[0] as BOSObjectTable;
            Debug.Assert(objectTable != null);
            Debug.Assert(objectTable.SelectedItems.Length == 1);

            var objectKey = objectTable.SelectedItems
                .Select(item => item.Cells[0].Text)
                .First();

            using (var objectMetaDataForm = new ObjectMetaDataForm(bosClient_, CurrentBucket_, objectKey))
            {
                objectMetaDataForm.ShowDialog();
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

        private void ObjectTable_SelectionChanged(object sender, XPTable.Events.SelectionEventArgs e)
        {
            var objectTable = sender as BOSObjectTable;
            Debug.Assert(objectTable != null);

            if (!toolStripProgressBar_.Visible)
                downloadToolStripButton_.Enabled = objectTable.SelectedItems.Length == 1;
            deleteToolStripButton_.Enabled = objectTable.SelectedItems.Length > 0;
            propertiesToolStripButton_.Enabled = objectTable.SelectedItems.Length == 1;
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

                    // If the ProgressBar is visible, it means we are uploading/downloading objects.
                    // So, we should not enable the `Upload` button, as the user may upload a new object.
                    if (!toolStripProgressBar_.Visible)
                        uploadToolStripButton_.Enabled = true;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this, 
                    "Failed to get bucket list:\n" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        private async void UpdateObjectList()
        {
            var tabPage = bucketTabControl_.SelectedTab;
            BOSObjectTable objectTable;
            if (tabPage.Controls.Count == 0)
            {
                objectTable = new BOSObjectTable();
                objectTable.Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Bottom;
                objectTable.Bounds = new Rectangle(4, 4, tabPage.Width - 8, tabPage.Height - 8);
                objectTable.DataSourceColumnBinder = new BOSObjectTableColumnBinder();
                objectTable.SelectionChanged += ObjectTable_SelectionChanged;

                tabPage.Controls.Add(objectTable);
            }
            else
            {
                objectTable = tabPage.Controls[0] as BOSObjectTable;
            }

            try
            {
                objectTable.BeginUpdate();
                objectTable.DataMember = "";
                objectTable.DataSource = await CreateObjectDataTable();
                objectTable.EndUpdate();
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    this,
                    "Failed to get object table:\n" + ex.Message,
                    "Error:",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }

            objectTable.AutoResizeColumnWidths(); // TODO
            //objectTable.SelectedItems.Clear(); // TODO

            downloadToolStripButton_.Enabled = objectTable.SelectedItems.Length > 0;
            deleteToolStripButton_.Enabled = objectTable.SelectedItems.Length > 0;
            propertiesToolStripButton_.Enabled = objectTable.SelectedItems.Length == 1;

            totalObjectsNumbertoolStripStatusLabel_.Text = objectTable.RowCount.ToString();
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

                    dataTable.Columns.Add("Progress");

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
// https://stackoverflow.com/questions/8750602/detect-when-a-form-has-been-closed-c-sharp
// https://stackoverflow.com/questions/2467133/c-sharp-listview-with-a-progressbar
// https://stackoverflow.com/questions/39181805/accessing-progressbar-in-listview
// https://stackoverflow.com/questions/9488176/how-do-i-update-progressbar-in-objectlistview-or-xptable
// https://stackoverflow.com/questions/37537765/uwp-update-multiple-progressbars-inside-listview
