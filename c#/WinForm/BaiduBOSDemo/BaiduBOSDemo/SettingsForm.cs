namespace BaiduBOSDemo
{
    using System.Windows.Forms;

    using MetroFramework.Forms;

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
            accessKeyTextBox_.Text = Settings.AccessKey;
            secretAccessKeyTextBox_.Text = Settings.SecretAccessKey;
            endPointTextBox_.Text = Settings.EndPoint;
            useFileFullPathAsObjectKeyMetroCheckBox_.Checked = Settings.UseFileFullPathAsObjectKey;
        }

        private void SettingsForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Settings = new Settings
            {
                AccessKey = accessKeyTextBox_.Text,
                SecretAccessKey = secretAccessKeyTextBox_.Text,
                EndPoint = endPointTextBox_.Text,
                UseFileFullPathAsObjectKey = useFileFullPathAsObjectKeyMetroCheckBox_.Checked
            };
        }
    }
}
