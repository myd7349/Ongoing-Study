namespace PlayWaveFileDemo
{
    using System;
    using System.Threading.Tasks;

    using Microsoft.DirectX.DirectSound;

    public class WaveOutDevice
    {
        public WaveOutDevice(Guid deviceGuid)
        {
            Guid = deviceGuid;
            Device = new Device(deviceGuid);
        }

        public Guid Guid
        {
            get;
            private set;
        }

        public Device Device
        {
            get;
            private set;
        }

        public DeviceInformation DeviceInformation
        {
            get;
            private set;
        }

        public override string ToString()
        {
            return DeviceInformation.Description;
        }

        public Caps Capabilities => Device.Caps;

        public static Task<WaveOutDevice[]> GetDevicesAsync()
        {
            return Task.Run(() => GetDevices());
        }

        public static WaveOutDevice[] GetDevices()
        {
            var deviceCollection = new DevicesCollection();
            var devices = new WaveOutDevice[deviceCollection.Count];

            for (int i = 0; i < devices.Length; ++i)
            {
                devices[i] = new WaveOutDevice(deviceCollection[i].DriverGuid)
                {
                    DeviceInformation = deviceCollection[i]
                };
            }

            return devices;
        }
    }
}
