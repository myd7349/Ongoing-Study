namespace TransparentFormDemo
{
    using System.Drawing;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            exitButton_.FlatAppearance.BorderColor = Color.FromArgb(0, 255, 255, 255); //transparent

            MouseDown += MainForm_MouseDown;
        }

        private void MainForm_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                User32.ReleaseCapture();
                User32.SendMessage(Handle, User32.WM_NCLBUTTONDOWN, User32.HT_CAPTION, 0);
            }
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            var bounds = ClientRectangle;
            bounds.Width -= 1;
            bounds.Height -= 1;

            e.Graphics.DrawRectangle(Pens.Green, bounds);
        }

        private void exitButton__Click(object sender, System.EventArgs e)
        {
            Close();
        }
    }
}


// References:
// [how can I make just the Form background transparent but not other controls](https://stackoverflow.com/questions/22631203/how-can-i-make-just-the-form-background-transparent-but-not-other-controls)
// [How to move a Windows Form when its FormBorderStyle property is set to None? [duplicate]](https://stackoverflow.com/questions/1241812/how-to-move-a-windows-form-when-its-formborderstyle-property-is-set-to-none)
// [Make a borderless form movable?](https://stackoverflow.com/questions/1592876/make-a-borderless-form-movable)
// [C# WinForms - custom button unwanted border when form unselected](https://stackoverflow.com/questions/9399215/c-sharp-winforms-custom-button-unwanted-border-when-form-unselected)
