namespace BluetoothDemoDotnetFramework
{
    using InTheHand.Net.Sockets;

    class BluetoothDeviceInfoEx
    {
        public BluetoothDeviceInfoEx(BluetoothDeviceInfo deviceInfo)
        {
            DeviceInfo = deviceInfo;
        }

        public BluetoothDeviceInfo DeviceInfo
        {
            get;
            private set;
        }

        public override string ToString()
        {
            if (DeviceInfo == null)
                return string.Empty;

            if (!string.IsNullOrWhiteSpace(DeviceInfo.DeviceName))
                return DeviceInfo.DeviceName;
            else
                return string.Format("{0}", DeviceInfo.DeviceAddress.ToString("C"));
        }
    }
}
