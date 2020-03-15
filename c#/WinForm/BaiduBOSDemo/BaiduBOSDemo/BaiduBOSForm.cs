namespace BaiduBOSDemo
{
    using System;
    using System.Data;
    using System.Drawing;
    using System.IO;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks;
    using System.Windows.Forms;

    using BaiduBce;
    using BaiduBce.Auth;
    using BaiduBce.Services.Bos;

    using BrightIdeasSoftware;

    using FastMember;

    using MetroFramework.Forms;

    using Humanizer.Bytes;

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
            var settings = Settings.Load();

            bosClient_ = CreateBosClient(settings);

            currentBucket_ = settings.CurrentBucket;

            var buckets = bosClient_.GetBuckets().ToArray();
            bucketTabControl_.TabPages.AddRange(buckets.Select(bucketName => new TabPage(bucketName)).ToArray());
            bucketTabControl_.TabPages.Add("+");

            if (buckets.Length > 0)
            {
                int index = bucketTabControl_.TabPages.IndexOfKey(currentBucket_);
                bucketTabControl_.SelectedIndex = index != -1 ? index : 0;
            }

            uploadButton_.Enabled = false;
        }

        private void BaiduBOSForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            var settings = Settings.Load();
            settings.CurrentBucket = currentBucket_;
            Settings.Store(settings);
        }

        private void settingsToolStripButton__Click(object sender, EventArgs e)
        {
            using (var settingsForm = new SettingsForm())
            {
                settingsForm.ShowDialog();
                bosClient_ = CreateBosClient(Settings.Load());
            }
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

        private void bucketTabControl__Selected(object sender, TabControlEventArgs e)
        {
            currentBucket_ = bucketTabControl_.SelectedTab.Text;

            UpdateObjectList();
        }

        private static BosClient CreateBosClient(Settings settings)
        {
            BceClientConfiguration clientConfig = new BceClientConfiguration();
            clientConfig.Credentials = new DefaultBceCredentials(settings.AccessKey, settings.SecretAccessKey);
            clientConfig.Endpoint = settings.EndPoint;

            return new BosClient(clientConfig);
        }

        private async void UpdateObjectList()
        {
            var tabPage = bucketTabControl_.SelectedTab;
            DataListView objectListView;
            if (tabPage.Controls.Count == 0)
            {
                objectListView = new DataListView();
                objectListView.Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Bottom;
                objectListView.Bounds = new Rectangle(4, 4, tabPage.Width - 8, tabPage.Height - 8);
                objectListView.View = View.Details;
                //objectListView.FullRowSelect = true;
                objectListView.GridLines = true;
                objectListView.ShowGroups = false;

                objectListView.UseCellFormatEvents = true;
                objectListView.FormatCell += delegate (object sender, FormatCellEventArgs e)
                {
                    if (e.ColumnIndex == 2)
                    {
                        long totalBytes;
                        if (long.TryParse(e.SubItem.Text, out totalBytes))
                            e.SubItem.Text = ByteSize.FromBytes(Convert.ToInt64(e.SubItem.Text)).ToString("0.##");
                    }
                };

                tabPage.Controls.Add(objectListView);

                objectListView.DataSource = await CreateObjectDataTable();

                var downloadColumn = new OLVColumn();
                downloadColumn.Text = "Action";
                downloadColumn.IsButton = true;
                downloadColumn.Sortable = false;
                downloadColumn.Width = 100;

                objectListView.AllColumns.Add(downloadColumn);

                objectListView.ButtonClick += ObjectListView_ButtonClick;
            }
            else
            {
                objectListView = tabPage.Controls[0] as DataListView;

                objectListView.DataSource = await CreateObjectDataTable();
            }

            objectListView.AutoResizeColumns();
        }

        private void ObjectListView_ButtonClick(object sender, CellClickEventArgs e)
        {
            MessageBox.Show(e.ColumnIndex.ToString());
        }

        private Task<DataTable> CreateObjectDataTable()
        {
            return Task.Run(
                () =>
                {
                    var objects = bosClient_.GetObjects(currentBucket_);
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

        private BosClient bosClient_;
        private string currentBucket_;
        private CancellationTokenSource cancellationTokenSource_;
    }
}
