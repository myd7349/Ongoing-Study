namespace UnhandledExceptionDemo
{
    using System;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void throwUnhandledExceptionButton__Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}
