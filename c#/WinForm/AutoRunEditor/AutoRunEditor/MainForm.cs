namespace AutoRunEditor
{
    using System.Windows.Forms;

    using Common;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            var autoRunApps = AutoRunHelper.GetAutoRunApplications();

            MessageBox.Show(autoRunApps.Length.ToString());
        }

    }
}
