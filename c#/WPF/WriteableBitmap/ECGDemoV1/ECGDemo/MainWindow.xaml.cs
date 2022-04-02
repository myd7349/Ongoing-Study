//#define USE_TASK

// Try this out:
#define IMAGE_STRETCH_NONE
//#define IMAGE_STRETCH_FILL
//#define IMAGE_STRETCH_UNIFORM
//#define IMAGE_STRETCH_UNIFORM_TO_FILL

//#define IMAGE_SnapsToDevicePixels

using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
#if USE_TASK
using System.Threading.Tasks;
#endif
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

using PInvoke;

using Microsoft.Samples.CustomControls;

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

            mainViewModel_ = new MainViewModel(StartAcquisition, StopAcquisition);
            DataContext = mainViewModel_;

#if IMAGE_STRETCH_NONE
            image_.Stretch = Stretch.None;
#elif IMAGE_STRETCH_FILL
            image_.Stretch = Stretch.Fill;
#elif IMAGE_STRETCH_UNIFORM
            image_.Stretch = Stretch.Uniform;
#elif IMAGE_STRETCH_UNIFORM_TO_FILL
            image_.Stretch = Stretch.UniformToFill;
#endif

#if IMAGE_SnapsToDevicePixels
            image_.SnapsToDevicePixels = true;
#endif

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
            var isCtrlKeyDown = Keyboard.IsKeyDown(Key.LeftCtrl) || Keyboard.IsKeyDown(Key.RightCtrl);
            if (isCtrlKeyDown)
                this.EasyTakeSnapshot();
            else
#if false
                imageCanvas_.EasyTakeSnapshot();
#else
                Snapshot.EasySaveBitmap(canvasBitmap_);
#endif
        }

        private void waveColorButton__Click(object sender, RoutedEventArgs e)
        {
            var colorPickerDialog = new ColorPickerDialog
            {
                StartingColor = WaveColor,
                Owner = this,
                WindowStartupLocation = WindowStartupLocation.CenterOwner,
            };
            if (colorPickerDialog.ShowDialog() == true)
                mainViewModel_.WaveColor = colorPickerDialog.SelectedColor;
        }

        private void refreshColorButton__Click(object sender, RoutedEventArgs e)
        {
            var colorPickerDialog = new ColorPickerDialog
            {
                StartingColor = RefreshColor,
                Owner = this,
                WindowStartupLocation = WindowStartupLocation.CenterOwner,
            };
            if (colorPickerDialog.ShowDialog() == true)
                mainViewModel_.RefreshColor = colorPickerDialog.SelectedColor;
        }

        private void imageCanvas__SizeChanged(object sender, SizeChangedEventArgs e)
        {
#if false
            // This will create a image with wrong height. As a result, if
            // we set image Stretch mode to None, then the waveform looks
            // discontinuous after restarting from left.
            // If we set Stretch mode to Uniform, then the waveforms looks
            // continuous, but we got a blurry bitmap.
            // So always keep in mind, in your XAML:
            //     <Canvas Name="imageCanvas_">
            //         <Image Name="image_" Grid.Row="0" Stretch="None" />
            //     </Canvas>
            // Just do not leave Image alone like this:
            //     <Window>
            //         <Image Name="image_" Grid.Row="0" Stretch="None" />
            //     </Window>
            var width = (int)ActualWidth;
            var height = (int)ActualHeight;
#else
            var width = (int)imageCanvas_.ActualWidth;
            var height = (int)imageCanvas_.ActualHeight;
#endif

            Debug.WriteLine($"Canvas Width: {width}, Height: {height}");
            Debug.WriteLine($"Image Width: {image_.ActualWidth}, Height: {image_.ActualHeight}");

            double dpiX, dpiY;
            GetDpi(out dpiX, out dpiY);
            dpiTextBlock_.Text = $"X: {dpiX} Y: {dpiY}";

            if (gridBitmap_ == null ||
                gridBitmap_.Width < width ||
                gridBitmap_.Height < height)
            {
                var stopwatch = Stopwatch.StartNew();

                gridBitmap_ = BitmapFactory.New(width, height);
                //gridBitmap_ = new WriteableBitmap(width, height, 96.0, 96.0, PixelFormats.Pbgra32, null);
                ECGrid.DrawDotted(gridBitmap_, BackColor, Grid5mmColor, Grid1mmColor, DotsPerMm);

                Debug.WriteLine($"It took {stopwatch.ElapsedMilliseconds}ms to draw grid on a {width}x{height} bitmap.");
            }

            var heightChanged = canvasBitmap_?.PixelHeight != height;

            canvasBitmap_ = BitmapFactory.New(width, height);
            //canvasBitmap_ = new WriteableBitmap(width, height, 96.0, 96.0, PixelFormats.Pbgra32, null);
            image_.Source = canvasBitmap_;
            image_.Stretch = Stretch.None;

            lastPointX_ = 0;
            BaselineY = canvasBitmap_.PixelHeight / 2;

            if (heightChanged)
                lastPointY_ = BaselineY;
        }

        private void GetDpi(out double dpiX, out double dpiY)
        {
#if false
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
#else
            var hdc = User32.GetDC(IntPtr.Zero);
            dpiX = Gdi32.GetDeviceCaps(hdc, Gdi32.DeviceCap.LOGPIXELSX);
            dpiY = Gdi32.GetDeviceCaps(hdc, Gdi32.DeviceCap.LOGPIXELSY);
#endif
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

            canvasBitmap_?.Clear(BackColor);

#if USE_TASK
            acquireTask_ = Task.Run(Acquire, cancellationTokenSource_.Token);
#else
            acquireThread_ = new Thread(Acquire);
            acquireThread_.Start();
#endif
        }

        private void StopAcquisition()
        {
            if (cancellationTokenSource_ == null)
                return;

            cancellationTokenSource_.Cancel();

#if USE_TASK
            acquireTask_.Wait();
#else
            acquireThread_.Join();
#endif

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

                    Action notifyError = () =>
                    {
                        lastErrorTextBlock_.Text = errorMessage;
                    };

                    Dispatcher.BeginInvoke(notifyError);

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
                var dirtyArea = new Rect(lastPointX_ + 1, 0, dirtyAreaWidth, canvasBitmap_.PixelHeight);

                canvasBitmap_.Blit(dirtyArea, gridBitmap_, dirtyArea);
                canvasBitmap_.FillRectangle(
                    (int)(lastPointX_ + voltages.Length * DotsPerSample + 1),
                    0,
                    (int)(lastPointX_ + dirtyAreaWidth + 1),
                    canvasBitmap_.PixelHeight,
                    RefreshColor);

                var lastX = (int)lastPointX_;

                double realX = 0;
                int x = 0;
                int y = 0;
                int count = 0;

                for (int i = 0; i < voltages.Length; ++i)
                {
                    // If voltages.Length == 1(SamplingRate == 10, for example),
                    // then (i + 1) makes a difference here.
                    realX = lastPointX_ + (count + 1) * DotsPerSample;

                    x = (int)realX;
                    y = (int)(BaselineY - voltages[i] * DotsPerMv);

                    if (x >= canvasBitmap_.PixelWidth)
                    {
                        //Debug.WriteLine($"{DateTime.Now:HH:mm:ss.fff} Restart from left at sample {i}:");
                        //Debug.WriteLine($"\tLast point: ({lastX}, {lastPointY_})");
                        //Debug.WriteLine($"\tNext point: (0, {y})");

                        lastPointX_ = 0;
                        count = 0;

                        lastX = 0;
                        lastPointY_ = y;

                        dirtyAreaWidth = (voltages.Length - i) * DotsPerSample + RefreshWidthInDots;
                        dirtyArea = new Rect(0, 0, dirtyAreaWidth, canvasBitmap_.PixelHeight);

                        canvasBitmap_.Blit(dirtyArea, gridBitmap_, dirtyArea);

                        continue;
                    }

                    canvasBitmap_.DrawLine(lastX, lastPointY_, x, y, WaveColor);

                    lastX = x;
                    lastPointY_ = y;

                    ++count;
                }

                lastPointX_ = realX;
            }

            var elapsedMs = stopwatch.ElapsedMilliseconds;
            drawWaveTextBlock_.Text = $"{elapsedMs}ms";
        }

        private MainViewModel mainViewModel_;

        private CancellationTokenSource cancellationTokenSource_;
#if USE_TASK
        private Task acquireTask_;
#else
        private Thread acquireThread_;
#endif
        private WriteableBitmap gridBitmap_;
        private WriteableBitmap canvasBitmap_;
        private double lastPointX_;
        private int lastPointY_;
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
// [How can I get the DPI in WPF?](https://stackoverflow.com/questions/1918877/how-can-i-get-the-dpi-in-wpf)
// [Wpf Dpi and pixel-perfect WritableBitmap](https://stackoverflow.com/questions/28562954/wpf-dpi-and-pixel-perfect-writablebitmap)
// [Screen Resolution Problem In WPF?](https://stackoverflow.com/questions/2236173/screen-resolution-problem-in-wpf)
// [How can I get the correct DPI of my screen in WPF?](https://stackoverflow.com/questions/54659859/how-can-i-get-the-correct-dpi-of-my-screen-in-wpf)
// [How can I get images in XAML to display as their actual size ?](https://stackoverflow.com/questions/1841511/how-can-i-get-images-in-xaml-to-display-as-their-actual-size)
// [WPF: How to display an image at its original size ?](https://stackoverflow.com/questions/3055550/wpf-how-to-display-an-image-at-its-original-size)
// [Blurry Bitmaps](https://docs.microsoft.com/en-us/archive/blogs/dwayneneed/blurry-bitmaps)
// [Image in WPF getting Blurry](https://stackoverflow.com/questions/5645274/image-in-wpf-getting-blurry)
// > SnapsToDevicePixels seems not working for bitmaps.
// >
// > The NearestNeighbor options actually converts the bitmap and will end up with
// > different one to the original bitmap.
// >
// > In WPF 4, a property "UseLayoutRounding" on the FrameworkElement is introduced
// > to solve this problem.
// >
// > By setting this property to True on your root element, such as Window will align
// > children elements on the edges of pixels.
// >
// <Window UseLayoutRounding="True">...</Window>
// [Reference external DLL in .NET Core project](https://stackoverflow.com/questions/40108106/reference-external-dll-in-net-core-project)
// https://github.com/Apress/practical-wpf-charts-graphics/blob/master/Examples_code/ColorsAndBrushes/ColorsAndBrushes/ColorPicker.xaml.cs
