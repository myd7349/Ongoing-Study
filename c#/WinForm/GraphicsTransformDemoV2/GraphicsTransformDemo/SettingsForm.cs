namespace GraphicsTransformDemo
{
    using System;
    using System.Windows.Forms;

    public partial class SettingsForm : Form
    {
        public SettingsForm(Settings settings)
        {
            settings_ = settings;

            InitializeComponent();

            xNumericUpDown_.ValueChanged += xNumericUpDown__ValueChanged;
            yNumericUpDown_.ValueChanged += yNumericUpDown__ValueChanged;
            widthNumericUpDown_.ValueChanged += widthNumericUpDown__ValueChanged;
            heightNumericUpDown_.ValueChanged += heightNumericUpDown__ValueChanged;
            angleNumericUpDown_.ValueChanged += angleNumericUpDown__ValueChanged;
        }

        public Settings Settings
        {
            get
            {
                return settings_;
            }

            set
            {
                settings_ = value;
            }
        }

        private void SettingsForm_VisibleChanged(object sender, EventArgs e)
        {
            if (Visible)
            {
                xNumericUpDown_.Value = settings_.X;
                yNumericUpDown_.Value = settings_.Y;
                widthNumericUpDown_.Value = settings_.Width;
                heightNumericUpDown_.Value = settings_.Height;
                angleNumericUpDown_.Value = settings_.Angle;
            }
        }

        private void SettingsForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
                Hide();
            }
        }

        private void xNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            settings_.X = Convert.ToInt32(xNumericUpDown_.Value);
        }

        private void yNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            settings_.Y = Convert.ToInt32(yNumericUpDown_.Value);
        }

        private void widthNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            settings_.Width = Convert.ToInt32(widthNumericUpDown_.Value);
        }

        private void heightNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            settings_.Height = Convert.ToInt32(heightNumericUpDown_.Value);
        }

        private void angleNumericUpDown__ValueChanged(object sender, System.EventArgs e)
        {
            settings_.Angle = Convert.ToInt32(angleNumericUpDown_.Value);
        }

        private Settings settings_;
    }
}


// References:
// [Hide form instead of closing when close button clicked](https://stackoverflow.com/questions/2021681/hide-form-instead-of-closing-when-close-button-clicked)
// [Event handling (Detect when hiding form)](https://stackoverflow.com/questions/9126057/event-handling-detect-when-hiding-form)
