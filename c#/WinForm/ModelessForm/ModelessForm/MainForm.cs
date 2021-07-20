namespace ModelessForm
{
    using System;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void modalButton__Click(object sender, EventArgs e)
        {
            using (var modalForm = new ModalForm())
            {
                var response = modalForm.ShowDialog();
                MessageBox.Show(response.ToString());
            }
        }

        private void modelessButton__Click(object sender, EventArgs e)
        {
            modelessMessageForm_.Owner = this;
            modelessMessageForm_.Show();
        }

        private ModelessForm modelessMessageForm_ = new ModelessForm();
    }
}
