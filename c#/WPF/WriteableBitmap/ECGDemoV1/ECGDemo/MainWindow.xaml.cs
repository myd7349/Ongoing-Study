//#define USE_TASK

using System;
using System.Buffers;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading;
#if USE_TASK
using System.Threading.Tasks;
#endif
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

using Common;

using FakeAD;


namespace ECGDemo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            cancellationTokenSource_ = new CancellationTokenSource();

#if USE_TASK
            acquireTask_ = Task.Run(Acquire, cancellationTokenSource_.Token);
#else
            acquireThread_ = new Thread(Acquire);
            acquireThread_.Start();
#endif
        }

        public double SamplingRate => ECGenerator.SamplingRate;

        public int DotsPerMm { get; set; } = 5;

        public double Speed { get; set; } = 25;

        public double Amplitude { get; set; } = 10;

        public double DotsPerSecond => DotsPerMm * Speed;

        public double DotsPerSample => DotsPerSecond / SamplingRate;

        public double DotsPerMv => DotsPerMm * Amplitude;

        public Color BackColor { get; set; } = Colors.Black;

        public Color Grid5mmColor { get; set; } = Colors.DarkGray;

        public Color Grid1mmColor { get; set; } = Colors.DarkGray;

        public Color WaveColor { get; set; } = Colors.LightGreen;

        public Color RefreshColor { get; set; } = Colors.White;

        public int RefreshWidthInDots { get; set; } = 2;

        private int LastPointX
        {
            get => lastPoint_[0];
            set => lastPoint_[0] = value;
        }

        private int LastPointY
        {
            get => lastPoint_[1];
            set => lastPoint_[1] = value;
        }

        private int BaselineY { get; set; }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            var width = (int)ActualWidth;
            var height = (int)ActualHeight;

            if (gridBitmap_ == null ||
                gridBitmap_.Width < width ||
                gridBitmap_.Height < height)
            {
                var stopwatch = Stopwatch.StartNew();

                gridBitmap_ = BitmapFactory.New(width, height);
                ECGrid.DrawDotted(gridBitmap_, BackColor, Grid5mmColor, Grid1mmColor, DotsPerMm);

                Debug.WriteLine($"It took {stopwatch.ElapsedMilliseconds}ms to draw grid on a {width}x{height} bitmap.");
            }

            canvasBitmap_ = BitmapFactory.New(width, height);
            image_.Source = canvasBitmap_;

            LastPointX = 0;
            BaselineY = canvasBitmap_.PixelHeight / 2;
        }

        protected override void OnClosed(EventArgs e)
        {
#if USE_TASK
            cancellationTokenSource_.Cancel();
            acquireTask_.Wait();
            cancellationTokenSource_.Dispose();
#else
            cancellationTokenSource_.Cancel();
            acquireThread_.Join();
            cancellationTokenSource_.Dispose();
#endif

            base.OnClosed(e);
        }

        private void Acquire()
        {
            CancellationToken token = cancellationTokenSource_.Token;

            Stopwatch stopwatch = new Stopwatch();

            var fakeAd = new FakeADWrapper(
                bytesPerSecond: (uint)(SamplingRate * ECGenerator.Channels * sizeof(double)),
                timeSliceInMilliseconds: ECGenerator.TimeSliceInMilliseconds,
                timeoutSliceCount: 3,
                port: 4321,
                callback: ECGenerator.GenerateECG,
                context: IntPtr.Zero);

            var samples = ECGenerator.SamplesPerTimeSlice;

            var bufferSizeInBytes =
                (ulong)samples * ECGenerator.Channels * sizeof(double);
            var buffer = new UnmanagedBuffer((int)bufferSizeInBytes);

            Debug.Assert(ECGenerator.Channels == 1);

            var voltages = new double[samples];

            while (true)
            {
                if (token.IsCancellationRequested)
                    break;

                stopwatch.Restart();

                var result = fakeAd.Read(buffer, bufferSizeInBytes);
                if (result != bufferSizeInBytes)
                {
                    var lastError = FakeADWrapper.GetLastError();
                    var lastErrorString = FakeADWrapper.ErrorToString(lastError);
                    var errorMessage = $"{lastError.ToString()} - {lastErrorString}";

                    Action notifyError = () =>
                    {
                        lastErrorTextBlock_.Text = errorMessage;
                    };

                    Dispatcher.BeginInvoke(notifyError);
                    break;
                }

                Marshal.Copy(buffer, voltages, 0, voltages.Length);

                var elapsedMs = stopwatch.ElapsedMilliseconds;

                Action updateTextBlock = () =>
                {
                    readDataTextBlock_.Text = $"{elapsedMs}ms";
                };
                Dispatcher.BeginInvoke(updateTextBlock);

#if false
                Dispatcher.Invoke(() => DrawWave(voltages)); // Deadlock when close the window.
#else
                Action drawWave = () => DrawWave(voltages);
                Dispatcher.BeginInvoke(drawWave);
#endif
            }

            fakeAd.Dispose();
        }

        private void DrawWave(double[] voltages)
        {
            Debug.Assert(CheckAccess());

            if (canvasBitmap_ == null)
                return;

            var stopwatch = Stopwatch.StartNew();

            using (var context = canvasBitmap_.GetBitmapContext())
            {
                var dirtyAreaWidth = voltages.Length * DotsPerSample + RefreshWidthInDots;
                var dirtyArea = new Rect(LastPointX + 1, 0, dirtyAreaWidth, canvasBitmap_.PixelHeight);

                canvasBitmap_.Blit(dirtyArea, gridBitmap_, dirtyArea);
                canvasBitmap_.FillRectangle(
                    (int)(LastPointX + voltages.Length * DotsPerSample + 1),
                    0,
                    (int)(LastPointX + dirtyAreaWidth),
                    canvasBitmap_.PixelHeight,
                    RefreshColor);

                var lastX = LastPointX;
                int x = 0;

                for (int i = 0; i < voltages.Length; ++i)
                {
                    x = (int)(LastPointX + i * DotsPerSample);
                    if (x >= canvasBitmap_.PixelWidth)
                    {
                        //Debug.WriteLine("Restart from left.");

                        x = 0;
                        lastX = 0;

                        dirtyAreaWidth = (voltages.Length - i) * DotsPerSample + RefreshWidthInDots;
                        dirtyArea = new Rect(0, 0, dirtyAreaWidth, canvasBitmap_.PixelHeight);

                        canvasBitmap_.Blit(dirtyArea, gridBitmap_, dirtyArea);
                    }

                    var y = (int)(BaselineY - voltages[i] * DotsPerMv);

                    canvasBitmap_.DrawLine(lastX, LastPointY, x, y, WaveColor);

                    lastX = x;
                    LastPointY = y;
                }

                LastPointX = x;
            }

            var elapsedMs = stopwatch.ElapsedMilliseconds;
            drawWaveTextBlock_.Text = $"{elapsedMs}ms";
        }

        private CancellationTokenSource cancellationTokenSource_;
#if USE_TASK
        private Task acquireTask_;
#else
        private Thread acquireThread_;
#endif
        private WriteableBitmap gridBitmap_;
        private WriteableBitmap canvasBitmap_;
        private int[] lastPoint_ = new int[2];
    }
}


// References:
// https://github.com/ScottPlot/ScottPlot/blob/d3b9c13b67d0344cf68e6e1cb7893fc0f1785e7f/src/ScottPlot4/ScottPlot/DataGen.cs#L807-L1007
// https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/how-to-cancel-a-task-and-its-children
// [How to edit a WritableBitmap.BackBuffer in non UI thread?](https://stackoverflow.com/questions/9868929/how-to-edit-a-writablebitmap-backbuffer-in-non-ui-thread)
// [WPF Problem with drawing Image multiple times using Thread and Dispatcher.Invoke](https://stackoverflow.com/questions/70740435/wpf-problem-with-drawing-image-multiple-times-using-thread-and-dispatcher-invoke)
// [C# Stream writeablebitmap among multiple threads](https://stackoverflow.com/questions/22830700/c-sharp-stream-writeablebitmap-among-multiple-threads)
// [Threading with WPF Images (System.InvalidOperationException)](https://stackoverflow.com/questions/5877447/threading-with-wpf-images-system-invalidoperationexception)
// [WPF BitmapFrame and multiple threads](https://stackoverflow.com/questions/4940447/wpf-bitmapframe-and-multiple-threads)
// [JpegBitmapEncoder and TLP finally got married](https://modosansreves-coding.blogspot.com/2011/12/jpegbitmapencoder-and-tlp-finally-got.html)
// [Best way to get a glow effect windows phone 7](https://stackoverflow.com/questions/3719750/best-way-to-get-a-glow-effect-windows-phone-7)
// [How can I render text on a WriteableBitmap on a background thread, in Windows Phone 7?](https://stackoverflow.com/questions/5666772/how-can-i-render-text-on-a-writeablebitmap-on-a-background-thread-in-windows-ph)
// [System.Threading.Tasks.TaskCanceledException: 'A task was canceled.' when Closing App](https://stackoverflow.com/questions/50370286/system-threading-tasks-taskcanceledexception-a-task-was-canceled-when-closin)
// [Deadlock when thread uses dispatcher and the main thread is waiting for thread to finish](https://stackoverflow.com/questions/24211934/deadlock-when-thread-uses-dispatcher-and-the-main-thread-is-waiting-for-thread-t)
// [InvokeRequired in wpf](https://stackoverflow.com/questions/15504826/invokerequired-in-wpf)
