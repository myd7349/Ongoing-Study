namespace NetMan
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows;
    using System.Windows.Threading;

    using MahApps.Metro.Controls;


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            FetchNetworkAdapterStatus();

            timer = new DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, 10);
            timer.Tick += Timer_Tick;
            timer.IsEnabled = true;
        }

        private void FetchNetworkAdapterStatus()
        {
            networkAdaptersDataGrid.DataContext = new NetworkAdaptersModel().Results;
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            FetchNetworkAdapterStatus();
        }

        private void ToggleSwitchButton_Click(object sender, RoutedEventArgs e)
        {
            var button = sender as ToggleSwitchButton;
            var index = (uint)button.Tag;

            var adapter = NetworkAdapterUtility.EnumerateNetworkAdapters(string.Format("Index={0}", index)).FirstOrDefault();
            Debug.Assert(adapter != null);

            if (button.IsChecked.HasValue)
            {
                timer.IsEnabled = false;

                var networkEnabled = button.IsChecked.Value;

#if false
                uint res = 0;
                if (networkEnabled)
                    res = adapter.Enable();
                else
                    res = adapter.Disable();

                Debug.Assert(res == 0);
#else
                var processInfo = new ProcessStartInfo("wmic",
                    string.Format(" path win32_networkadapter where index={0} call {1}", index, networkEnabled ? "enable" : "disable"));
                processInfo.WindowStyle = ProcessWindowStyle.Hidden;
                Process.Start(processInfo);
#endif

                timer.IsEnabled = true;
            }
        }

        private DispatcherTimer timer;
    }
}

// References:
// https://msdn.microsoft.com/en-us/library/aa394216(v=vs.85).aspx
// https://stackoverflow.com/questions/14164105/optimizing-wmi-query-with-linq
// https://stackoverflow.com/questions/172875/how-to-disable-enable-network-connection-in-c-sharp
// https://stackoverflow.com/questions/3053372/programmatically-enable-disable-connection
// http://www.cnblogs.com/nickli/archive/2010/10/07/1845175.html
// https://stackoverflow.com/questions/20770438/how-to-bind-datatable-to-datagrid
// https://stackoverflow.com/questions/564366/convert-generic-list-enumerable-to-datatable
// https://stackoverflow.com/questions/5410430/wpf-timer-like-c-sharp-timer
