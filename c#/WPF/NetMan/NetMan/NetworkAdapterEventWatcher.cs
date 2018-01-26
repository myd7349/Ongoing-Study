namespace NetMan
{
    using System;
    using System.Management;

    using ROOT.CIMV2.Win32;

    public delegate void NetworkAdapterEvent(object sender, NetworkAdapter e);

    public class NetworkAdapterEventWatcher : IDisposable
    {
        public NetworkAdapterEventWatcher(string computerName = "localhost", string user = "", string pwd = "")
        {
            if (!computerName.Equals("localhost", StringComparison.OrdinalIgnoreCase))
            {
                ConnectionOptions connOption = new ConnectionOptions();
                connOption.Username = user;
                connOption.Password = pwd;
                connOption.Authority = "ntlmdomain:DOMAIN";
                scope = new ManagementScope(String.Format("\\\\{0}\\root\\CIMV2", computerName), connOption);
            }
            else
            {
                scope = new ManagementScope(String.Format("\\\\{0}\\root\\CIMV2", computerName), null);
            }

            scope.Connect();

            eventWatcher = new ManagementEventWatcher(scope, new EventQuery(WmiQuery));
            eventWatcher.EventArrived += EventWatcher_EventArrived;
            eventWatcher.Start();
        }

        public event NetworkAdapterEvent NetworkAdapterEventArrived;

        public void Dispose()
        {
            eventWatcher.Stop();
        }

        private void EventWatcher_EventArrived(object sender, EventArrivedEventArgs e)
        {
            NetworkAdapterEventArrived?.Invoke(sender, 
                new NetworkAdapter((ManagementBaseObject)e.NewEvent.Properties["TargetInstance"].Value));
        }

        private static string WmiQuery = "Select * From __InstanceModificationEvent Within 1 Where TargetInstance ISA 'Win32_NetworkAdapter'";

        private ManagementEventWatcher eventWatcher;
        private ManagementScope scope;
    }
}

// References:
// https://stackoverflow.com/questions/16355306/how-to-subscribe-a-specific-network-adapter-connection-event-in-net
