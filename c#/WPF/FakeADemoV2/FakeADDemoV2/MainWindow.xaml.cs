namespace FakeADDemoV2
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows;
    using System.Windows.Media;
    using System.Windows.Threading;

    using Microsoft.Research.DynamicDataDisplay.DataSources;

    using FakeAD;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            adDataLineGraph_.DataSource = dataSource_;
            adDataLineGraph_.LinePen = new Pen(Brushes.Blue, 2.0);
            adDataChart_.LegendVisible = true;
            adDataChart_.FitToView();

#if ViaProducerConsumerDataFlow
            ad_ = new FakeADViaProducerConsumerDataFlow
            {
                Channels = 1,
                SamplingRate = 4000,
            };
#elif ViaBlockingCollection
            ad_ = new FakeADViaBlockingCollection
            {
                Channels = 1,
                SamplingRate = 4000,
            };
#elif ViaUDP
            ad_ = new FakeADViaUDP
            {
                Channels = 1,
                SamplingRate = 4000,
            };
#endif
            ad_.Open(Samples);
            buffer_ = new double[Samples];
            samples_ = 0;

            dispatcherTimer_.Interval = TimeSpan.FromMilliseconds(Samples / ad_.SamplingRate * 1000);
            dispatcherTimer_.Tick += DispatcherTimer__Tick;
            dispatcherTimer_.IsEnabled = true;

            stopwatch_ = Stopwatch.StartNew();
            previousTimePoint_ = stopwatch_.ElapsedMilliseconds;
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            ad_.Release();
        }

        private void DispatcherTimer__Tick(object sender, EventArgs e)
        {
            ad_.Read(buffer_, 0, buffer_.Length);
            dataSource_.AppendMany(
                buffer_.Select(
                    value => new Point(samples_++ / ad_.SamplingRate, value)
                ));

            double xLeftLimit = Math.Max(0, samples_ / ad_.SamplingRate - SecondsPerScreen);
            adDataChart_.Viewport.Visible = new Rect(
                xLeftLimit,
                -1.5,
                SecondsPerScreen,
                3.0
                );

            var ellapsedMs = stopwatch_.ElapsedMilliseconds;
            if (ellapsedMs - previousTimePoint_ >= 1000)
            {
                var samplingRate = (double)samples_ / ellapsedMs * 1000;
                Debug.WriteLine("Sampling Rate: {0} / {1} = {2}", samples_, ellapsedMs, samplingRate);
                previousTimePoint_ = ellapsedMs;
            }
        }

        private const int Samples = 100;
        private const int SecondsPerScreen = 10;
        private ObservableDataSource<Point> dataSource_ = new ObservableDataSource<Point>();
        private DispatcherTimer dispatcherTimer_ = new DispatcherTimer();
        private FakeADBase ad_;
        private double[] buffer_;
        private long samples_;
        private Stopwatch stopwatch_;
        private long previousTimePoint_;
    }
}

// References:
// https://github.com/mesta1/DynamicDataDisplay-example
// [DynamicDataDisplay ChartPlotter scroll horizontal axis](https://stackoverflow.com/questions/13546068/dynamicdatadisplay-chartplotter-scroll-horizontal-axis)
// https://blog.csdn.net/u013187531/article/details/72137401
// https://www.mesta-automation.com/real-time-line-charts-with-wpf-and-dynamic-data-display/
