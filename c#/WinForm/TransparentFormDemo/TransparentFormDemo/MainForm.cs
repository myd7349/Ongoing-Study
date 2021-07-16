namespace TransparentFormDemo
{
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void exitButton__Click(object sender, System.EventArgs e)
        {
            Close();
        }
    }
}


// References:
// [how can I make just the Form background transparent but not other controls](https://stackoverflow.com/questions/22631203/how-can-i-make-just-the-form-background-transparent-but-not-other-controls)
