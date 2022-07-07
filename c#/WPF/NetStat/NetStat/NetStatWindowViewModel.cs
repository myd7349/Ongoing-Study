using System.Collections.ObjectModel;
using System.Net.NetworkInformation;

using CommunityToolkit.Mvvm.ComponentModel;
using MvvmDialogs;

namespace NetStat
{
    internal class NetStatWindowViewModel : ObservableObject, IModalDialogViewModel
    {
        public NetStatWindowViewModel()
        {
            NetStatEntries = new ObservableCollection<NetStatEntry>();

            GetNetStatEntries();
        }
        
        public ObservableCollection<NetStatEntry> NetStatEntries { get; }
        
        public bool? DialogResult { get; }

        private void GetNetStatEntries()
        {
            var ipGlobalProperties = IPGlobalProperties.GetIPGlobalProperties();

            int id = 1;
            
            // TCP
            foreach (var ipEndPoint in ipGlobalProperties.GetActiveTcpListeners())
            {
                var netStatEntry = new NetStatEntry
                {
                    Id = id++,
                    ProtocolType = "TCP",
                    LocalAddress = ipEndPoint,
                    State = TcpState.Listen,
                };

                NetStatEntries.Add(netStatEntry);
            }
            
            foreach (var tcpConnectionInformation in ipGlobalProperties.GetActiveTcpConnections())
            {
                var netStatEntry = new NetStatEntry
                {
                    Id = id++,
                    ProtocolType = "TCP",
                    LocalAddress = tcpConnectionInformation.LocalEndPoint,
                    ForeignAddress = tcpConnectionInformation.RemoteEndPoint,
                    State = tcpConnectionInformation.State,
                };

                NetStatEntries.Add(netStatEntry);
            }

            // UDP
            foreach (var ipEndPoint in ipGlobalProperties.GetActiveUdpListeners())
            {
                var netStatEntry = new NetStatEntry
                {
                    Id = id++,
                    ProtocolType = "UDP",
                    LocalAddress = ipEndPoint,
                };

                NetStatEntries.Add(netStatEntry);
            }
        }
    }
}


// References:
// [In C#, how to check if a TCP port is available?](https://stackoverflow.com/questions/570098/in-c-how-to-check-if-a-tcp-port-is-available)
// [How to determine tcp port used by Windows process in C#](https://stackoverflow.com/questions/1819364/how-to-determine-tcp-port-used-by-windows-process-in-c-sharp)
// [Build your own netstat.exe with c#](https://timvw.be/2007/09/09/build-your-own-netstat.exe-with-c/)
