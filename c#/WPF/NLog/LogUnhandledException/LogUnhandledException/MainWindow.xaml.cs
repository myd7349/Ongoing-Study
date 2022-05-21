using System;
using System.Windows;

using NLog;

using Common;


namespace LogUnhandledException
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private Logger Log = LogManager.GetCurrentClassLogger();

        private void crushMeButton__Click(object sender, RoutedEventArgs e)
        {
            Log.Info("Crush Me!");
            throw new Exception("Crush Me!");
        }

        private void tryCrushMeAgainButton__Click(object sender, RoutedEventArgs e)
        {
            Log.Info("Try Crush Me Again!");

            if (timer_ == null)
            {
                timer_ = new MMTimer(TimerCallback, null, null, false)
                {
                    Interval = 50,
                    IsPeriodic = true,
                };
                timer_.Start();
            }
        }

        private void TimerCallback(object arg)
        {
            Log.Info("Timer callback.");

            var result = 10 / GetMagicNumber();
            Log.Info($"Result: {result}");
        }

        private int GetMagicNumber()
        {
            return 0;
        }

        private MMTimer timer_;
    }
}
