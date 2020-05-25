namespace CPUPerformanceCounter
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Threading.Tasks;
    using System.Windows;
    using System.Windows.Media;
    using System.Windows.Threading;

    using Microsoft.Research.DynamicDataDisplay;
    using Microsoft.Research.DynamicDataDisplay.DataSources;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private double RefreshIntervalInSeconds_
        {
            get
            {
                return 1.0;
            }
        }

        private double MaximumVisibleSeconds_
        {
            get
            {
                return 60.0;
            }
        }

        private int PerformanceCounterCacheQueueMaximumSize_
        {
            get
            {
                return (int)(MaximumVisibleSeconds_ / RefreshIntervalInSeconds_);
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            cpuPerformanceChart_.AddLineGraph(dataSource_, Colors.Blue, 2.0, "Percentage");
            cpuPerformanceChart_.LegendVisible = true;

            dispatcherTimer_.Interval = TimeSpan.FromSeconds(RefreshIntervalInSeconds_);
            dispatcherTimer_.Tick += DispatcherTimer__Tick;
            dispatcherTimer_.IsEnabled = true;

            cpuPerformanceChart_.FitToView();
        }

        private async void DispatcherTimer__Tick(object sender, EventArgs e)
        {
            performanceCounter_.CategoryName = "Processor";
            performanceCounter_.CounterName = "% Processor Time";
            performanceCounter_.InstanceName = "_Total";

            double x = currentSecond_;
            double y = await Task.Run(() => performanceCounter_.NextValue());
            Point point = new Point(x, y);
            dataSource_.AppendAsync(Dispatcher, point);

            if (performanceCounterCacheQueue_ == null)
                performanceCounterCacheQueue_ = new Queue<double>();

            if (performanceCounterCacheQueue_.Count == PerformanceCounterCacheQueueMaximumSize_)
                performanceCounterCacheQueue_.Dequeue();

            performanceCounterCacheQueue_.Enqueue(y);

            if (autoScrollCheckBox_.IsChecked ?? false)
            {
                cpuPerformanceChart_.Viewport.Visible = new Rect(
                    Math.Max((int)(currentSecond_ - MaximumVisibleSeconds_), 0),
                    0,
                    MaximumVisibleSeconds_,
                    performanceCounterCacheQueue_.Max()
                    );
            }

            currentSecond_++;
        }

        private ObservableDataSource<Point> dataSource_ = new ObservableDataSource<Point>();
        private PerformanceCounter performanceCounter_ = new PerformanceCounter();
        private DispatcherTimer dispatcherTimer_ = new DispatcherTimer();
        private int currentSecond_ = 0;
        private Queue<double> performanceCounterCacheQueue_;
    }
}

// References:
// https://github.com/mesta1/DynamicDataDisplay-example
// [DynamicDataDisplay ChartPlotter scroll horizontal axis](https://stackoverflow.com/questions/13546068/dynamicdatadisplay-chartplotter-scroll-horizontal-axis)
// https://blog.csdn.net/u013187531/article/details/72137401
// https://blog.csdn.net/wangshubo1989/article/details/46875243
// https://github.com/step-up-labs/firebase-database-dotnet/issues/148
// https://github.com/step-up-labs/firebase-database-dotnet/issues/155
// https://stackoverflow.com/questions/3485727/textbox-text-centering
// https://stackoverflow.com/questions/2079552/wpf-textbox-validation
// https://stackoverflow.com/questions/19539492/implement-validation-for-wpf-textboxes
// https://stackoverflow.com/questions/13135235/disable-text-box-when-check-box-is-unchecked-during-run-time-in-c-sharp
// https://www.cnblogs.com/anjou/p/9593537.html
// https://stackoverflow.com/questions/14701029/get-average-cpu-usage-of-a-computer-in-last-x-minute
// https://stackoverflow.com/questions/278071/how-to-get-the-cpu-usage-in-c/6168408#6168408
