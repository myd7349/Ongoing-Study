namespace Common.Win32
{
    using System.Collections.Generic;

    using Microsoft.Win32;

    public static class RegistryHelper
    {
        // SerialPort.GetPortNames()
        public static Dictionary<string, string> GetAvailableSerialPorts()
        {
            var availablePortsMap = new Dictionary<string, string>();

            var portsSubkey = Registry.LocalMachine.OpenSubKey(PORTS_SUBKEY);

            foreach (var portName in portsSubkey.GetValueNames())
                availablePortsMap[portName] = portsSubkey.GetValue(portName) as string;
            
            portsSubkey.Close();

            return availablePortsMap;
        }

        private const string PORTS_SUBKEY = "HARDWARE\\DEVICEMAP\\SERIALCOMM";
    }
}
