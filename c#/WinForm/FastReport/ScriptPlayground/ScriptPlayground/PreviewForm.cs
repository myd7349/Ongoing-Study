namespace ScriptPlayground
{
    using System;
    using System.Drawing;
    using System.Windows.Forms;

    public partial class PreviewForm : Form
    {
        public PreviewForm(Image report)
        {
            InitializeComponent();

            pictureBox_.Image = report;
        }
    }
}
