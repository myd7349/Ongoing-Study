namespace NetMan
{
    using System.Diagnostics;
    using System.Linq;
    using System.Windows;

    using MahApps.Metro.Controls;

    using ROOT.CIMV2.Win32;


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            FetchNetworkAdapterStatus();

            eventWatcher = new NetworkAdapterEventWatcher();
            eventWatcher.NetworkAdapterEventArrived += EventWatcher_NetworkAdapterEventArrived;
        }

        private void EventWatcher_NetworkAdapterEventArrived(object sender, NetworkAdapter e)
        {
            MessageBox.Show(e.Name + (e.NetEnabled ? " Enabled" : " not Enabled")
                + (e.NetConnectionStatus == 2 ? " , Connected" : " , Disconnected"));

            FetchNetworkAdapterStatus();
        }

        private void FetchNetworkAdapterStatus()
        {
            networkAdaptersListView.DataContext = new NetworkAdaptersModel().Results;
        }

        private void ToggleSwitchButton_Click(object sender, RoutedEventArgs e)
        {
            var button = sender as ToggleSwitchButton;
            var index = (uint)button.Tag;

            var adapter = NetworkAdapterUtility.EnumerateNetworkAdapters(string.Format("Index={0}", index)).FirstOrDefault();
            Debug.Assert(adapter != null);

            if (button.IsChecked.HasValue)
            {
                var isNetEnabled = button.IsChecked.Value;

#if false
                uint res = 0;
                if (networkEnabled)
                    res = adapter.Enable();
                else
                    res = adapter.Disable();

                Debug.Assert(res == 0);
#else
                var processInfo = new ProcessStartInfo("wmic",
                    string.Format(" path win32_networkadapter where index={0} call {1}", index, isNetEnabled ? "enable" : "disable"));
                processInfo.WindowStyle = ProcessWindowStyle.Hidden;
                Process.Start(processInfo);
#endif
            }
        }

        private NetworkAdapterEventWatcher eventWatcher;
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
