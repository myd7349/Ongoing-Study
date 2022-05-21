using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

using SkiaSharp;
using SkiaSharp.WPF;

using Common;
using Common.WPF;

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

            mainViewModel_ = new MainViewModel(StartAcquisition, StopAcquisition);
            DataContext = mainViewModel_;

            // Without this line, the image will got blurry sometimes.
            // For example, there are two ToolBars in the main ToolBarTray.
            // If you drag the second toolbar below the first one, the waveform
            // becomes blurred(Snapshots/Snapshot_2022-03-27_21-30-53.765.png).
            //imageCanvas_.UseLayoutRounding = true;
            UseLayoutRounding = true;
        }

        public int DotsPerMm { get; set; } = 5;

        public int SamplingRate => mainViewModel_.SamplingRate;

        public double Speed => mainViewModel_.Speed;

        public double Amplitude => mainViewModel_.Amplitude;

        public double DotsPerSecond => DotsPerMm * Speed;

        public double DotsPerSample => DotsPerSecond / SamplingRate;

        public double DotsPerMv => DotsPerMm * Amplitude;

        public Color BackColor { get; set; } = Colors.Black;

        public Color Grid5mmColor { get; set; } = Colors.DarkGray;

        public Color Grid1mmColor { get; set; } = Colors.DarkGray;

        public Color WaveColor => mainViewModel_.WaveColor;

        public Color RefreshColor => mainViewModel_.RefreshColor;

        public int RefreshWidthInDots { get; set; } = 2;

        private int BaselineY { get; set; }

        private void takeSnapshotButton__Click(object sender, RoutedEventArgs e)
        {
            using (var context = canvasBitmap_.CreateSurfaceContext())
            {
                var image = context.Surface.Snapshot();
                var filePath = Snapshot.GetSaveFileName();
                if (!string.IsNullOrEmpty(filePath))
                {
                    var extension = Path.GetExtension(filePath);
                    var format = Snapshot.GetImageFormat(extension);
                    image.Save(filePath, format, 100);
                }
            }
        }

        private void imageCanvas__SizeChanged(object sender, SizeChangedEventArgs e)
        {
            var width = (int)imageCanvas_.ActualWidth;
            var height = (int)imageCanvas_.ActualHeight;

            Debug.WriteLine($"Canvas Width: {width}, Height: {height}");
            Debug.WriteLine($"Image Width: {image_.ActualWidth}, Height: {image_.ActualHeight}");

            double dpiX, dpiY;
            GetDpi(out dpiX, out dpiY);
            dpiTextBlock_.Text = $"X: {dpiX} Y: {dpiY}";

            if (gridImage_ == null ||
                gridImage_.Width < width ||
                gridImage_.Height < height)
            {
                var stopwatch = Stopwatch.StartNew();

                var imageInfo = new SKImageInfo(width, height, SKImageInfo.PlatformColorType, SKAlphaType.Premul);
                gridImage_ = SKImage.Create(imageInfo);

#if false
                using (var bitmap = SKBitmap.FromImage(gridImage_))
                using (var canvas = new SKCanvas(bitmap))
                {
#else
                using (var surface = SKSurface.Create(gridImage_.PeekPixels()))
                {
                    var canvas = surface.Canvas;
#endif
                    ECGrid.DrawDotted(canvas, width, height,
                        BackColor.ToSKColor(),
                        Grid5mmColor.ToSKColor(),
                        Grid1mmColor.ToSKColor(),
                        DotsPerMm);
                }

                Debug.WriteLine($"It took {stopwatch.ElapsedMilliseconds}ms to draw grid on a {width}x{height} bitmap.");
            }

            var heightChanged = canvasBitmap_?.PixelHeight != height;

            canvasBitmap_ = new WriteableBitmap(
                width, height, 96, 96, PixelFormats.Bgr32, null);

            image_.Source = canvasBitmap_;
            image_.Stretch = Stretch.None;

            lastPointX_ = 0;
            BaselineY = canvasBitmap_.PixelHeight / 2;

            if (heightChanged)
                lastPointY_ = BaselineY;
        }

        private void GetDpi(out double dpiX, out double dpiY)
        {
            PresentationSource source = PresentationSource.FromVisual(this);
            if (source != null)
            {
                dpiX = 96.0 * source.CompositionTarget.TransformToDevice.M11;
                dpiY = 96.0 * source.CompositionTarget.TransformToDevice.M22;
            }
            else
            {
                dpiX = 0;
                dpiY = 0;
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            StopAcquisition();

            base.OnClosed(e);
        }

        private void StartAcquisition()
        {
            if (cancellationTokenSource_ != null)
                return;

            cancellationTokenSource_ = new CancellationTokenSource();

            lastPointX_ = 0;
            lastPointY_ = BaselineY;

            using (var context = canvasBitmap_.CreateSurfaceContext())
            {
                context.Canvas.Clear(BackColor.ToSKColor());
                canvasBitmap_.AddDirtyRect(0, 0, canvasBitmap_.PixelWidth, canvasBitmap_.PixelHeight);
            }

            acquireThread_ = new Thread(Acquire);
            acquireThread_.Start();
        }

        private void StopAcquisition()
        {
            if (cancellationTokenSource_ == null)
                return;

            cancellationTokenSource_.Cancel();

            acquireThread_.Join();

            cancellationTokenSource_.Dispose();
            cancellationTokenSource_ = null;
        }

        private void Acquire()
        {
            CancellationToken token = cancellationTokenSource_.Token;

            Stopwatch stopwatch = new Stopwatch();

            var timeSliceInMilliseconds = mainViewModel_.ECGenerator.CalculateBestTimeSlice();

            var fakeAdCallback = new FakeADCallback64(mainViewModel_.ECGenerator.GenerateECG);
            var fakeAd = new FakeADWrapper(
                bytesPerSecond: (uint)(SamplingRate * ECGenerator.Channels * sizeof(double)),
                timeSliceInMilliseconds: (uint)timeSliceInMilliseconds,
                timeoutSliceCount: 3,
                port: 4321,
                callback: fakeAdCallback,
                context: IntPtr.Zero);

            var samples = SamplingRate * timeSliceInMilliseconds / 1000;

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

                    Dispatcher.InvokeAsync(() => lastErrorTextBlock_.Text = errorMessage);

                    if (lastError == Error.Timeout)
                    {
                        Thread.Sleep(timeSliceInMilliseconds);
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }

                Marshal.Copy(buffer, voltages, 0, voltages.Length);

                var elapsedMs = stopwatch.ElapsedMilliseconds;

                Dispatcher.InvokeAsync(() => readDataTextBlock_.Text = $"{elapsedMs}ms");

                Dispatcher.InvokeAsync(() => DrawWave(voltages));
            }

            fakeAd.Dispose();
        }

        private void DrawWave(double[] voltages)
        {
            Debug.Assert(CheckAccess());

            if (canvasBitmap_ == null)
                return;

            var stopwatch = Stopwatch.StartNew();

            using (var context = canvasBitmap_.CreateSurfaceContext())
            using (var paint = new SKPaint())
            {
                var canvas = context.Canvas;

                var dirtyAreaWidth = voltages.Length * DotsPerSample + RefreshWidthInDots;

                // SKRect.Create
                var dirtyArea = new SKRect(
                    (float)(lastPointX_ + 1),
                    0, 
                    (float)(lastPointX_ + 1 + dirtyAreaWidth),
                    canvasBitmap_.PixelHeight);

                canvas.DrawImage(gridImage_, dirtyArea, dirtyArea);
                //Debug.WriteLine($"Clear range: {dirtyArea.Left} -> {dirtyArea.Right}");

#if false
                var refreshRect = new SKRect(
                    (int)(dirtyArea.Right + 0.5) - RefreshWidthInDots,
                    0,
                    (int)(dirtyArea.Right + 0.5),
                    dirtyArea.Bottom);
#else
                var refreshRect = new SKRect(
                    (float)(lastPointX_ + 1 + voltages.Length * DotsPerSample),
                    0,
                    dirtyArea.Right,
                    dirtyArea.Bottom);
#endif
                paint.Color = RefreshColor.ToSKColor();
                canvas.DrawRect(refreshRect, paint);

                canvasBitmap_.AddDirtyRectAutoAdjust(
                    // Change it to (int)dirtyArea.Left, and see what happens.
#if false
                    (int)dirtyArea.Left,
#else
                    (int)dirtyArea.Left - 1,
#endif
                    0,
                    // Change it to (int)dirtyAreaWidth, and see what happens.
#if false
                    (int)dirtyAreaWidth,
#else
                    (int)(dirtyAreaWidth + RefreshWidthInDots),
#endif
                    canvasBitmap_.PixelHeight);

                var lastX = lastPointX_;

                double realX = 0;
                float x = 0;
                float y = 0;
                int count = 0;

                for (int i = 0; i < voltages.Length; ++i)
                {
                    // If voltages.Length == 1(SamplingRate == 10, for example),
                    // then (i + 1) makes a difference here.
                    realX = lastPointX_ + (count + 1) * DotsPerSample;

                    x = (float)realX;
                    y = (float)(BaselineY - voltages[i] * DotsPerMv);

                    if (x >= canvasBitmap_.PixelWidth)
                    {
                        canvas.DrawLine(lastX, lastPointY_, x, y, WaveColor.ToSKColor());

                        x -= canvasBitmap_.PixelWidth;

                        dirtyAreaWidth = (voltages.Length - i - 1) * DotsPerSample +
                            x + RefreshWidthInDots;
                        dirtyArea = new SKRect(0, 0, (float)dirtyAreaWidth, canvasBitmap_.PixelHeight);

                        canvas.DrawImage(gridImage_, dirtyArea, dirtyArea);

                        canvas.DrawLine(
                            lastX - canvasBitmap_.PixelWidth,
                            lastPointY_,
                            x,
                            y,
                            WaveColor.ToSKColor());

                        canvasBitmap_.AddDirtyRectAutoAdjust(
                            0, 0, (int)dirtyAreaWidth, canvasBitmap_.PixelHeight);

                        lastPointX_ = x;
                        count = 0;

                        lastX = lastPointX_;
                        lastPointY_ = y;

                        // What if voltages.Length == 1?
                        // (SamplingRate == 5, for example.)
                        realX = x;
 
                        continue;
                    }

                    canvas.DrawLine(lastX, lastPointY_, x, y, WaveColor.ToSKColor());
                    //Debug.WriteLine($"{i} Line: {lastX},{lastPointY_} -> {x},{y}");

                    lastX = x;
                    lastPointY_ = y;

                    ++count;
                }

                lastPointX_ = (float)realX;

                //canvasBitmap_.AddDirtyRect(0, 0, canvasBitmap_.PixelWidth, canvasBitmap_.PixelHeight);
            }

            var elapsedMs = stopwatch.ElapsedMilliseconds;
            drawWaveTextBlock_.Text = $"{elapsedMs}ms";
        }

        private MainViewModel mainViewModel_;

        private CancellationTokenSource cancellationTokenSource_;
        private Thread acquireThread_;
        private SKImage gridImage_;
        private WriteableBitmap canvasBitmap_;
        private float lastPointX_;
        private float lastPointY_;
    }
}


// References:
// [深入了解 WPF Dispatcher 的工作原理（Invoke/InvokeAsync 部分）](https://blog.walterlv.com/post/dotnet/2017/09/26/dispatcher-invoke-async.html)
