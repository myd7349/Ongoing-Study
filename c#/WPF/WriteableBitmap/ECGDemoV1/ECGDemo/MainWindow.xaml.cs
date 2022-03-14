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
            acquireTask_ = Task.Run(
                () => Acquire(cancellationTokenSource_.Token),
                cancellationTokenSource_.Token);
#else
            acquireThread_ = new Thread(Acquire);
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

            lock (canvasBitmapLock_)
            {
                canvasBitmap_ = BitmapFactory.New(width, height);
                image_.Source = canvasBitmap_;

                LastPointX = 0;
                BaselineY = canvasBitmap_.PixelHeight / 2;
            }
        }

        protected override void OnClosed(EventArgs e)
        {
#if USE_TASK
            cancellationTokenSource_.Cancel();
            acquireTask_.Wait();
            cancellationTokenSource_.Dispose();
#else
#endif

            base.OnClosed(e);
        }

#if USE_TASK
        private void Acquire(CancellationToken token)
        {
#else
        private void Acquire()
        {
            CancellationToken token = cancellationTokenSource_.Token;
#endif
            Stopwatch stopwatch_ = Stopwatch.StartNew();
            int samples_ = 0;

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
            var points = new int[samples * 2];

            while (true)
            {
                if (token.IsCancellationRequested)
                    break;

                if (fakeAd.Read(buffer, bufferSizeInBytes) != bufferSizeInBytes)
                    break;

                Marshal.Copy(buffer, voltages, 0, voltages.Length);

                int c = -1;

                lock (canvasBitmapLock_)
                {
                    if (canvasBitmap_ == null)
                        continue;

                    for (int i = 0; i < samples; ++i)
                    {
                        var x = (int)(LastPointX + i * DotsPerSample);
                        if (x >= canvasBitmap_.PixelWidth)
                        {
                            if (c == -1)
                                c = i;

                            x = (int)((i - c) * DotsPerSample);
                        }

                        points[i * 2] = x;
                        points[i * 2 + 1] = (int)(BaselineY - voltages[i] * DotsPerMv);
                    }
                }

                totalSamplesTextBlock_.Text = $"{samples_ += 25}";

                canvasBitmap_.Freeze();

                Dispatcher.Invoke(() =>
                {
                    if (canvasBitmap_ == null)
                        return;

                    using (canvasBitmap_.GetBitmapContext())
                    {
                        if (c == -1)
                        {
                            var dirtyAreaWidth = samples * DotsPerSample + RefreshWidthInDots;
                            var dirtyArea = new Rect(points[0] + 1, 0, dirtyAreaWidth, canvasBitmap_.PixelHeight);

                            canvasBitmap_.Blit(dirtyArea, gridBitmap_, dirtyArea);

                            canvasBitmap_.FillRectangle(
                                (int)(points[0] + samples * DotsPerSample + 1),
                                0,
                                (int)(points[0] + dirtyAreaWidth),
                                canvasBitmap_.PixelHeight,
                                RefreshColor);

                            canvasBitmap_.DrawLine(LastPointX, LastPointY, points[0], points[1], WaveColor);
                            canvasBitmap_.DrawPolyline(points, WaveColor);
                        }
                        else
                        {
                            var dirtyArea1Width = c > 0 ? (points[(c - 1) * 2] - points[0]) : 0;
                            if (dirtyArea1Width > 0)
                            {
                                var dirtyArea1 = new Rect(
                                    points[0],
                                    0,
                                    dirtyArea1Width,
                                    canvasBitmap_.PixelHeight);

                                canvasBitmap_.Blit(dirtyArea1, gridBitmap_, dirtyArea1);
                                canvasBitmap_.DrawLine(LastPointX, LastPointY, points[0], points[1], WaveColor);
                                canvasBitmap_.DrawPolyline(points.Take(c * 2).ToArray(), WaveColor);
                            }

                            Debug.WriteLine($"Restart from left.");

                            var dirtyArea2 = new Rect(
                                0,
                                0,
                                points[(samples - 1) * 2] - points[c * 2] + RefreshWidthInDots,
                                canvasBitmap_.PixelHeight);
                            canvasBitmap_.Blit(dirtyArea2, gridBitmap_, dirtyArea2);
                            canvasBitmap_.DrawPolyline(points.Skip(c * 2).ToArray(), WaveColor);
                        }
                    }

                    image_.Source = canvasBitmap_;

                    LastPointX = points[(samples - 1) * 2];
                    LastPointY = points[points.Length - 1];
                });
            }

            /*
            elapsedMsTextBlock_.Text = $"{stopwatch_.ElapsedMilliseconds}ms";

            var stopwatch = Stopwatch.StartNew();


            acquireDataTextBlock_.Text = $"{samples} samples in {stopwatch.ElapsedMilliseconds}ms";

            stopwatch.Restart();

            drawWaveTextBlock_.Text = $"{stopwatch.ElapsedMilliseconds}ms";

            totalSamplesTextBlock_.Text = samples_.ToString();

            Debug.WriteLine($"X Start: {LastPointX}");
            */
        }

        private CancellationTokenSource cancellationTokenSource_;
#if USE_TASK
        private Task acquireTask_;
#else
        private Thread acquireThread_;
#endif
        private WriteableBitmap gridBitmap_;
        private WriteableBitmap canvasBitmap_;
        private object canvasBitmapLock_ = new object();
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
