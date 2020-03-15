namespace BaiduBOSDemo
{
    using System.Windows.Forms;

    public partial class SettingsForm : Form
    {
        public SettingsForm()
        {
            InitializeComponent();
        }

        private void SettingsForm_Load(object sender, System.EventArgs e)
        {
            var settings = Settings.Load();

            accessKeyTextBox_.Text = settings.AccessKey;
            secretAccessKeyTextBox_.Text = settings.SecretAccessKey;
            endPointTextBox_.Text = settings.EndPoint;
        }

        private void SettingsForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Settings.Store(
                new Settings
                {
                    AccessKey = accessKeyTextBox_.Text,
                    SecretAccessKey = secretAccessKeyTextBox_.Text,
                    EndPoint = endPointTextBox_.Text
                });
        }
    }
}
