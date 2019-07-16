namespace FakeADemo
{
    using System;
    using System.Drawing;
    using System.Threading;
    using System.Windows.Forms;

    using FakeAD;

    public partial class FakeADemoForm : Form
    {
        private delegate void UpdateViewDelegate(short[] data);
        private Thread thread_;
        private bool isRunning_;

        public FakeADemoForm()
        {
            InitializeComponent();
        }

        private void FakeADemoForm_Layout(object sender, LayoutEventArgs e)
        {
            var plotArea = new Rectangle
            {
                X = ClientRectangle.X,
                Y = mainMenuStrip.Bottom,
                Width = ClientRectangle.Width,
                Height = ClientRectangle.Height - mainMenuStrip.Height,
            };
        }

        private void startToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (thread_ == null)
            {
                Start();
                startToolStripMenuItem.Text = "Stop";
                startToolStripMenuItem.ToolTipText = "Stop";
            }
            else
            {
                Stop();
                startToolStripMenuItem.Text = "Start";
                startToolStripMenuItem.ToolTipText = "Start";
            }
        }

        private void FakeADemoForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            Stop();
        }

        private void Start()
        {
            if (thread_ == null)
            {
                isRunning_ = true;
                thread_ = new Thread(ThreadProc);
                thread_.IsBackground = false;
                thread_.Start();
            }
        }

        private void Stop()
        {
            if (thread_ != null)
            {
                isRunning_ = false;
                thread_.Join();
                thread_ = null;
            }
        }

        private void UpdateView(short[] data)
        {
        }

        private void ThreadProc()
        {
            var samples = 256;

            using (var ad = new FakeAD(samples))
            {
                if (!ad.IsOpened)
                    return;

                var buffer = new short[samples];

                while (isRunning_) // FIXME:
                {
                    if (ad.Read(buffer) == samples)
                    {
                        BeginInvoke(new UpdateViewDelegate(UpdateView), buffer);
                    }
                }

                ad.Release();
            }
        }
    }
}


// References:
// https://stackoverflow.com/questions/24808291/reading-an-int-thats-updated-by-interlocked-on-other-threads
