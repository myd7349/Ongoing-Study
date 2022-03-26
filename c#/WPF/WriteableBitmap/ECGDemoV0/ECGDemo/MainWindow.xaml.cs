//#define USE_ARRAY_POOL

//#define USE_RENDERING_CALLBACK
//#define USE_DISPATCHERTIMER
#define USE_MMTIMER
//#define USE_TIMERQUEUETIMER

using System;
using System.Buffers;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#if USE_DISPATCHERTIMER
using System.Windows.Threading;
#endif

using ScottPlot;

#if USE_MMTIMER || USE_TIMERQUEUETIMER
using Common;
#endif

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

            mainThreadId_ = Thread.CurrentThread.ManagedThreadId;

            ecgGenerator_ = new DataGen.Electrocardiogram();

#if USE_RENDERING_CALLBACK
            CompositionTarget.Rendering += CompositionTarget_Rendering;
#elif USE_DISPATCHERTIMER
            timer_ = new DispatcherTimer();
            timer_.Tick += Timer__Tick;
            timer_.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timer_.Start();
#elif USE_MMTIMER
            timer_ = new MMTimer(Timer__Tick)
            {
                Interval = 50,
            };
            timer_.Start();
#elif USE_TIMERQUEUETIMER
            cancellationTokenSource_ = new CancellationTokenSource();
            timer_ = new TimerQueueTimer();
            waitOrTimerDelegate_ = new WaitOrTimerDelegate(Timer__Tick); // Avoid GC
            timer_.Create(1000, 50, waitOrTimerDelegate_);
#endif

            stopwatch_ = Stopwatch.StartNew();
        }

        public double SamplingRate { get; set; } = 500;

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

#if false
                gridBitmap_ = new WriteableBitmap(
                    width, height, 96, 96,
                    PixelFormats.Bgr32, null);
#else
                gridBitmap_ = BitmapFactory.New(width, height);
#endif
                ECGrid.DrawDotted(gridBitmap_, BackColor, Grid5mmColor, Grid1mmColor, DotsPerMm);

                Debug.WriteLine($"It took {stopwatch.ElapsedMilliseconds}ms to draw grid on a {width}x{height} bitmap.");
            }

            canvasBitmap_ = BitmapFactory.New(width, height);

            image_.Source = canvasBitmap_;

            LastPointX = 0;
            BaselineY = canvasBitmap_.PixelHeight / 2;
        }

#if USE_RENDERING_CALLBACK
        private void CompositionTarget_Rendering(object sender, EventArgs e)
#elif USE_DISPATCHERTIMER
        private void Timer__Tick(object sender, EventArgs e)
#elif USE_MMTIMER
        private void Timer__Tick(object context)
#elif USE_TIMERQUEUETIMER
        private void Timer__Tick(IntPtr lpParameter, bool timerOrWaitFired)
#endif
        {
#if USE_TIMERQUEUETIMER
            Action render = Render;
            if (!cancellationTokenSource_.IsCancellationRequested)
                Dispatcher.BeginInvoke(render);
#else
            Render();
#endif
        }

        private void Render()
        {
#if USE_RENDERING_CALLBACK
            if (rendering_)
                return;

            var renderingTimePointInMilliseconds = stopwatch_.ElapsedMilliseconds;
            if (renderingTimePointInMilliseconds - lastRenderingTimePointInMilliseconds_ < 50)
                return;
#endif

            Debug.Assert(Thread.CurrentThread.ManagedThreadId == mainThreadId_);

            if (canvasBitmap_ == null)
                return;

            var elapsedSeconds = stopwatch_.ElapsedMilliseconds / 1000.0;
            var expectedSamples = (int)(elapsedSeconds * SamplingRate);
            var samples = expectedSamples - samples_;

            if (samples < 2)
                return;

#if USE_RENDERING_CALLBACK
            rendering_ = true;
#endif

            var stopwatch = Stopwatch.StartNew();

#if USE_ARRAY_POOL
            var points = ArrayPool<int>.Shared.Rent(samples * 2);
            Debug.Assert(points.Length == samples * 2);
#else
            var points = new int[samples * 2];
#endif

            int c = -1;
            for (int i = 0; i < samples; ++i)
            {
                double voltage = ecgGenerator_.GetVoltage((samples_ + i) / SamplingRate);

                var x = (int)(LastPointX + i * DotsPerSample);
                if (x >= canvasBitmap_.PixelWidth)
                {
                    if (c == -1)
                        c = i;

                    x = (int)((i - c) * DotsPerSample);
                }

                points[i * 2] = x;
                points[i * 2 + 1] = (int)(BaselineY - voltage * DotsPerMv);
            }

            samplesTextBlock_.Text = samples.ToString();
            acquireDataTextBlock_.Text = $"{stopwatch.ElapsedMilliseconds}ms";

            stopwatch.Restart();

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

            drawWaveTextBlock_.Text = $"{stopwatch.ElapsedMilliseconds}ms";

            LastPointX = points[(samples - 1) * 2];
            LastPointY = points[points.Length - 1];

#if USE_ARRAY_POOL
            ArrayPool<int>.Shared.Return(points);
#endif

            samples_ = expectedSamples;

            elapsedMsTextBlock_.Text = $"{stopwatch_.ElapsedMilliseconds}ms";
            totalSamplesTextBlock_.Text = samples_.ToString();
            samplingRateTextBlock_.Text = $"{samples_ * 1000 / stopwatch_.ElapsedMilliseconds}";

            Debug.WriteLine($"X Start: {LastPointX}");

#if USE_RENDERING_CALLBACK
            lastRenderingTimePointInMilliseconds_ = renderingTimePointInMilliseconds;
            rendering_ = false;
#endif
        }

        protected override void OnClosed(EventArgs e)
        {
#if USE_TIMERQUEUETIMER
            cancellationTokenSource_.Cancel();
#endif

            base.OnClosed(e);
        }

        private int mainThreadId_;
        private WriteableBitmap gridBitmap_;
        private WriteableBitmap canvasBitmap_;
        private DataGen.Electrocardiogram ecgGenerator_;

#if USE_RENDERING_CALLBACK
        private long lastRenderingTimePointInMilliseconds_;
        private bool rendering_ = false;
#elif USE_DISPATCHERTIMER
        private DispatcherTimer timer_;
#elif USE_MMTIMER
        private MMTimer timer_;
#elif USE_TIMERQUEUETIMER
        private readonly WaitOrTimerDelegate waitOrTimerDelegate_;
        private TimerQueueTimer timer_;
        private readonly CancellationTokenSource cancellationTokenSource_;
#endif

        private Stopwatch stopwatch_;
        private int samples_ = 0;
        private int[] lastPoint_ = new int[2];
    }
}


// References:
// [How do I create a timer in WPF?](https://stackoverflow.com/questions/11559999/how-do-i-create-a-timer-in-wpf)
// https://github.com/ScottPlot/ScottPlot/blob/d3b9c13b67d0344cf68e6e1cb7893fc0f1785e7f/src/ScottPlot4/ScottPlot/DataGen.cs#L807-L1007
// [Difference between Synchronization Context and Dispatcher](https://stackoverflow.com/questions/24671883/difference-between-synchronization-context-and-dispatcher)
// [System.Threading.Tasks.TaskCanceledException: 'A task was canceled.' when Closing App](https://stackoverflow.com/questions/50370286/system-threading-tasks-taskcanceledexception-a-task-was-canceled-when-closin)
