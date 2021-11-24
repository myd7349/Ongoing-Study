namespace NetMan
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Windows;
    using System.Windows.Threading;

    using MahApps.Metro.Controls;
    using ToastNotifications;
    using ToastNotifications.Core;
    using ToastNotifications.Lifetime;
    using ToastNotifications.Messages;
    using ToastNotifications.Position;

    using ROOT.CIMV2.Win32;


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            notifier_ = new Notifier(
                config =>
                {
                    config.PositionProvider = new PrimaryScreenPositionProvider(Corner.BottomRight, 5, 5);
                    config.LifetimeSupervisor = new TimeAndCountBasedLifetimeSupervisor(
                        TimeSpan.FromSeconds(5), MaximumNotificationCount.FromCount(5));
                    //config.Dispatcher = Dispatcher.CurrentDispatcher;
                    config.DisplayOptions.TopMost = true;
                    config.DisplayOptions.Width = 420;
                });

            Application.Current.MainWindow.Closing += MainWindow_Closing;

            FetchNetworkAdapterStatus();

            eventWatcher = new NetworkAdapterEventWatcher();
            eventWatcher.NetworkAdapterEventArrived += EventWatcher_NetworkAdapterEventArrived;
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            notifier_?.Dispose();
        }

        private void EventWatcher_NetworkAdapterEventArrived(object sender, NetworkAdapter e)
        {
            var message = string.Format("{0}:\r\nEnabled: {1}\r\nConnected: {2}",
                e.Name, e.NetEnabled, e.NetConnectionStatus == 2);

            var messageOptions = new MessageOptions
            {
                FreezeOnMouseEnter = true,
                ShowCloseButton = true,
                FontSize = 15,
            };
            notifier_.ShowInformation(message, messageOptions);

            FetchNetworkAdapterStatus();
        }

        private void FetchNetworkAdapterStatus()
        {
            Dispatcher.BeginInvoke(new Action(
                () => networkAdaptersListView.DataContext = new NetworkAdaptersModel().Results));
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
        private Notifier notifier_;
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
