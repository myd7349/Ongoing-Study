namespace NetMan
{
    using System.Collections.Generic;
    using System.Management;

    using ROOT.CIMV2.Win32;

    public static class NetworkAdapterUtility
    {
        public static IEnumerable<NetworkAdapter> EnumerateNetworkAdapters(string condition = "")
        {
            using (var searcher = new ManagementObjectSearcher(new SelectQuery("Win32_NetworkAdapter", condition)))
            {
                foreach (var mo in searcher.Get())
                    yield return new NetworkAdapter(mo);
            }
        }
    }
}
