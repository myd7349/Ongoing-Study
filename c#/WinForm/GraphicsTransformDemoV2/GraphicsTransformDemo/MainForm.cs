namespace GraphicsTransformDemo
{
    using System;
    using System.Diagnostics;
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Threading;
    using System.Windows.Forms;

    using Common;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            settings_ = new Settings(w: 120, h: 80);
            settingsLock_ = new object();

            settingsForm_ = new SettingsForm(settings_);
            settingsForm_.Owner = this;

            showSettingsForm_ = 1;

            settingsUpdatedEvent_ = new ManualResetEvent(false);

            InitializeComponent();
        }

        private void MainForm_Load(object sender, System.EventArgs e)
        {
            axisPen_ = new Pen(Color.Black, 1F)
            {
                DashStyle = DashStyle.Dot
            };

            curvePen_ = new Pen(Color.Blue, 2F);

            running_ = true;
            thread_ = new Thread(ThreadCallback);
            thread_.Start();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            running_ = false;

            if (showSettingsForm_ == 1)
                settingsUpdatedEvent_.Set();

            thread_.Join();
        }

        private void MainForm_Layout(object sender, LayoutEventArgs e)
        {
            ReLayout();
            canvas_.Invalidate();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            ReLayout();
            canvas_.Invalidate();
        }

        private void canvas__Paint(object sender, PaintEventArgs e)
        {
            if (canvas_.ClientRectangle.IsEmpty)
                return;

            lock (settingsLock_)
            {
                Render(e.Graphics);
            }
        }

        private void Render(Graphics graphics)
        {
            var oldClip = graphics.Clip;
            var clipRectangle = canvasBounds_;
            clipRectangle.Inflate(1, 1);
            graphics.Clip = new Region(clipRectangle);

            var oldSmoothingMode = graphics.SmoothingMode;
            graphics.SmoothingMode = SmoothingMode.AntiAlias;

            // 0. Background
            //graphics.Clear(Color.White);
            graphics.FillRectangle(Brushes.White, canvasBounds_);

            // 1. Axis
            graphics.DrawLine(axisPen_, canvasBounds_.Left, origin_.Y, canvasBounds_.Right, origin_.Y);
            graphics.DrawLine(axisPen_, origin_.X, canvasBounds_.Top, origin_.X, canvasBounds_.Bottom);

            // 2. Coordinate system
            graphics.TranslateTransform(origin_.X, origin_.Y);
            graphics.ScaleTransform(1F, -1F);

            graphics.FillEllipse(Brushes.Black, -2, -2, 4, 4);

            var radians = MathHelper.ConvertDegreesToRadians(settings_.Angle) + Math.Atan2(settings_.Height, settings_.Width);
            var hypotenuse = MathHelper.Hypotenuse(settings_.Width / 2.0, settings_.Height / 2.0);
            var xOffset = hypotenuse * Math.Cos(radians);
            var yOffset = hypotenuse * Math.Sin(radians);
            graphics.TranslateTransform((float)-xOffset, (float)-yOffset);

            graphics.RotateTransform(settings_.Angle);

            // 3. Ellipse
            graphics.FillEllipse(Brushes.Black, -2, -2, 4, 4);
            graphics.DrawRectangle(axisPen_, settings_.X, settings_.Y, settings_.Width, settings_.Height);
            graphics.DrawEllipse(curvePen_, settings_.X, settings_.Y, settings_.Width, settings_.Height);

            graphics.SmoothingMode = oldSmoothingMode;

            graphics.Clip = oldClip;
        }

        private void ReLayout()
        {
            canvasBounds_ = new Rectangle
            {
                X = 1,
                Y = 1,
                Width = canvas_.ClientRectangle.Width - 2,
                Height = canvas_.ClientRectangle.Height - 2,
            };

            origin_ = new Point(
                (canvasBounds_.Left + canvasBounds_.Right) / 2,
                (canvasBounds_.Top + canvasBounds_.Bottom) / 2);
        }

        private void ThreadCallback()
        {
            while (running_)
            {
                if (showSettingsForm_ == 1)
                {
                    ShowSettingsForm();

                    settingsUpdatedEvent_.WaitOne();
                    settingsUpdatedEvent_.Reset();

                    showSettingsForm_ = 0;
                }
                else
                {
                    Thread.Sleep(50);

                    lock (settingsLock_)
                    {
                        settings_.Angle += 1;
                        if (settings_.Angle >= 360)
                            settings_.Angle = 0;
                    }

                    // If we use `Invoke` here, there will be a deadlock when
                    // the main form is closed.
#if false
                    Invoke(new Action(() => canvas_.Invalidate()));
#else
                    BeginInvoke(new Action(() => canvas_.Invalidate()));
#endif
                }
            }
        }

        private void ShowSettingsForm()
        {
            Debug.Assert(InvokeRequired);

            if (InvokeRequired)
            {
                Invoke(new Action(() =>
                    {
                        lock (settingsLock_)
                        {
                            settingsForm_.Settings = settings_;
                        }

                        settingsForm_.FormClosing += settingsForm__FormClosing;
                        settingsForm_.Show();
                    }));
            }
        }

        private void settingsForm__FormClosing(object sender, FormClosingEventArgs e)
        {
            settingsForm_.FormClosing -= settingsForm__FormClosing;

            lock (settingsLock_)
            {
                settings_ = settingsForm_.Settings;
            }

            settingsUpdatedEvent_.Set();
        }

        private void showSettingsFormToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Interlocked.CompareExchange(ref showSettingsForm_, 1, 0);
        }

        private Rectangle canvasBounds_;
        private Point origin_;
        private Pen axisPen_;
        private Pen curvePen_;
        private Settings settings_;
        private object settingsLock_;
        private SettingsForm settingsForm_;
        private Thread thread_;
        private bool running_;
        private int showSettingsForm_;
        private ManualResetEvent settingsUpdatedEvent_;
    }
}


// References:
// [flip coordinates when drawing to control](https://stackoverflow.com/questions/1485745/flip-coordinates-when-drawing-to-control)
// [Get and Set Screen Resolution](https://stackoverflow.com/questions/5082610/get-and-set-screen-resolution)
// [How to detect when a windows form is being minimized?](https://stackoverflow.com/questions/1052913/how-to-detect-when-a-windows-form-is-being-minimized)
// [Call MessageBox from async thread with Form1 as parent](https://stackoverflow.com/questions/5349524/call-messagebox-from-async-thread-with-form1-as-parent)
// [Displaying a non modal dialog in c# and getting a callback when the form is close](https://stackoverflow.com/questions/29987853/displaying-a-non-modal-dialog-in-c-sharp-and-getting-a-callback-when-the-form-is)
// [C# Is value type assignment atomic?](https://stackoverflow.com/questions/53601121/c-sharp-is-value-type-assignment-atomic)
// [Context Menu Item is not showing when form is running](https://stackoverflow.com/questions/37487205/context-menu-item-is-not-showing-when-form-is-running)
// [C#: Avoid flickering when painting?](https://stackoverflow.com/questions/40679194/c-avoid-flickering-when-painting)
// [c# flickering Listview on update](https://stackoverflow.com/questions/442817/c-sharp-flickering-listview-on-update)
