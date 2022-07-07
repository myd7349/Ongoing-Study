using System.Net;
using System.Net.NetworkInformation;

namespace NetStat
{
    internal class NetStatEntry
    {
        public int Id { get; set; }

        public string? ProtocolType { get; set; }
        
        public IPEndPoint? LocalAddress { get; set; }

        public string? LocalAddressString => LocalAddress?.ToString();

        public IPEndPoint? ForeignAddress { get; set; }

        public string? ForeignAddressString => ForeignAddress?.ToString();

        public TcpState? State { get; set; }

        public string? Process { get; set; }
    }
}
