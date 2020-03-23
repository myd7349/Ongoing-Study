namespace BaiduBOSDemo
{
    using System.Windows.Forms;

    using MetroFramework.Forms;

    using Humanizer.Bytes;

    public partial class SettingsForm : MetroForm
    {
        public SettingsForm(Settings settings)
        {
            Settings = settings;

            InitializeComponent();
        }

        public Settings Settings
        {
            get;
            private set;
        }

        private void SettingsForm_Load(object sender, System.EventArgs e)
        {
            // Account settings
            accessKeyTextBox_.Text = Settings.AccessKey;
            secretAccessKeyTextBox_.Text = Settings.SecretAccessKey;
            endPointTextBox_.Text = Settings.EndPoint;

            // Upload settings
            var uploadPartSize = ByteSize.FromBytes(Settings.UploadPartSize);
            if (Settings.UploadPartSize >= 1024 * 1024)
            {
                uploadPartSizeMetroTextBox_.Text = uploadPartSize.Megabytes.ToString();
                uploadPartSizeUnitMetroComboBox_.SelectedIndex = 1;
            }
            else
            {
                uploadPartSizeMetroTextBox_.Text = uploadPartSize.Kilobytes.ToString();
                uploadPartSizeUnitMetroComboBox_.SelectedIndex = 0;
            }
            
            useFileFullPathAsObjectKeyMetroCheckBox_.Checked = Settings.UseFileFullPathAsObjectKey;

            // Download settings
            var downloadSize = ByteSize.FromBytes(Settings.DownloadSize);
            if (Settings.DownloadSize >= 1024 * 1024)
            {
                downloadSizeMetroTextBox_.Text = downloadSize.Megabytes.ToString();
                downloadSizeUnitMetroComboBox_.SelectedIndex = 2;
            }
            else if (Settings.DownloadSize >= 1024)
            {
                downloadSizeMetroTextBox_.Text = downloadSize.Kilobytes.ToString();
                downloadSizeUnitMetroComboBox_.SelectedIndex = 1;
            }
            else
            {
                downloadSizeMetroTextBox_.Text = downloadSize.Bytes.ToString();
                downloadSizeUnitMetroComboBox_.SelectedIndex = 0;
            }
        }

        private void SettingsForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            var readableUploadPartSize = uploadPartSizeMetroTextBox_.Text + uploadPartSizeUnitMetroComboBox_.SelectedItem.ToString();
            ByteSize uploadByteSize;

            var readableDownloadSize = downloadSizeMetroTextBox_.Text + downloadSizeUnitMetroComboBox_.SelectedItem.ToString();
            ByteSize downloadSize;
            
            Settings = new Settings
            {
                AccessKey = accessKeyTextBox_.Text,
                SecretAccessKey = secretAccessKeyTextBox_.Text,
                EndPoint = endPointTextBox_.Text,
                UploadPartSize = ByteSize.TryParse(readableUploadPartSize, out uploadByteSize) ? (long)uploadByteSize.Bytes : 0,
                UseFileFullPathAsObjectKey = useFileFullPathAsObjectKeyMetroCheckBox_.Checked,
                DownloadSize = ByteSize.TryParse(readableDownloadSize, out downloadSize) ? (long)downloadSize.Bytes : 0,
                CurrentBucket = Settings.CurrentBucket,
            };
        }
    }
}
