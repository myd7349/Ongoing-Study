namespace ShowTips
{
    using System;
    using System.Drawing;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            toolTip_.SetToolTip(textBox_, "So tell me what you are going to say?");
            toolTip_.SetToolTip(balloonCheckBox_, "Do you like balloons?");
            toolTip_.SetToolTip(showToolTipbutton_, "Click me and I will tell you something.");
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (WindowState != FormWindowState.Minimized)
            {
                e.Cancel = true;
                WindowState = FormWindowState.Minimized;

                notifyIcon_.Tag = string.Empty;
                notifyIcon_.ShowBalloonTip(
                    3000,
                    Text,
                     "Left double click: Show me again!\r\nRight click: Show context menu.",
                     ToolTipIcon.Info);
            }
        }

        private void balloonCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            toolTip_.IsBalloon = balloonCheckBox_.Checked;
        }

        private void showToolTipbutton__Click(object sender, EventArgs e)
        {
            if (dynamicToolTip_ != null)
                dynamicToolTip_.Dispose();

            dynamicToolTip_ = new ToolTip
            {
                ToolTipTitle = "Your PC says:",
                IsBalloon = balloonCheckBox_.Checked,
                BackColor = Color.SkyBlue,
            };

            dynamicToolTip_.Show(string.Empty, textBox_, 0);
            dynamicToolTip_.Show(textBox_.Text, textBox_);

            notifyIcon_.BalloonTipTitle = "Your PC says:";
            notifyIcon_.BalloonTipText = textBox_.Text;
            notifyIcon_.ShowBalloonTip(1000);
        }

        private void notifyIcon__MouseDoubleClick(object sender, MouseEventArgs e)
        {
            ShowForm();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void ShowForm()
        {
            if (WindowState == FormWindowState.Minimized)
            {
                Show();
                WindowState = FormWindowState.Normal;
            }

            Activate();
            Focus();
        }

        private ToolTip dynamicToolTip_;
    }
}

// References:
// [How do I make a tooltip point at a specific label in C#?](https://stackoverflow.com/questions/7627185/how-do-i-make-a-tooltip-point-at-a-specific-label-in-c/7627228#7627228)
// [How to show a .NET Balloon ToolTip?](https://stackoverflow.com/questions/8716917/how-to-show-a-net-balloon-tooltip)
// [How do I add a ToolTip to a control?](https://stackoverflow.com/questions/1339524/how-do-i-add-a-tooltip-to-a-control)
// https://github.com/hbons/SparkleShare/blob/master/SparkleShare/Windows/UserInterface/Bubbles.cs
// [C# tooltip doesn't display long enough](https://stackoverflow.com/questions/8225807/c-sharp-tooltip-doesnt-display-long-enough)
// [[WinApp]写个简单的NotifyIcon(TrayIcon)小程式](https://dotblogs.com.tw/rainmaker/2011/03/10/21773)
// https://github.com/rocksdanister/lively/blob/dev-v1.0-fluent-netcore/src/livelywpf/livelywpf/Systray.cs
