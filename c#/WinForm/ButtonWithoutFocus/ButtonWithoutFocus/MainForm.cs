namespace ButtonWithoutFocus
{
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void retryButton__Click(object sender, System.EventArgs e)
        {
            MessageBox.Show("Retry");
        }

        private void retryNoFocusButton__Click(object sender, System.EventArgs e)
        {
            MessageBox.Show("Retry (No Focus)");
        }
    }
}
