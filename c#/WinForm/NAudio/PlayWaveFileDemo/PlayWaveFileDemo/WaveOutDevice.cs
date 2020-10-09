namespace PlayWaveFileDemo
{
    using System.Diagnostics;
    using System.Runtime.InteropServices;

    using NAudio.CoreAudioApi;
    using NAudio.Wave;

    public class WaveOutDevice
    {
        public WaveOutDevice(int deviceNumber)
            : this(deviceNumber, WaveOut.GetCapabilities(deviceNumber))
        {
        }

        public WaveOutDevice(int deviceNumber, WaveOutCapabilities capabilities)
        {
            DeviceNumber = deviceNumber;
            Capabilities = capabilities;
        }

        public override string ToString()
        {
            return string.Format("#{0}: {1}", DeviceNumber, ProductName);
        }

        public int DeviceNumber
        {
            get;
            private set;
        }

        public WaveOutCapabilities Capabilities
        {
            get;
            private set;
        }

        public string ProductName
        {
            get;
            private set;
        }

        public static WaveOutDevice[] GetDevices()
        {
            MMDeviceEnumerator enumerator = new MMDeviceEnumerator();

            var devices = new WaveOutDevice[WaveOut.DeviceCount];
            for (int i = 0; i < devices.Length; ++i)
            {
                // MSDN:
                // If the value specified by the uDeviceID parameter is a device identifier,
                // it can vary from zero to one less than the number of devices present. 
                devices[i] = new WaveOutDevice(i);

                foreach (MMDevice device in enumerator.EnumerateAudioEndPoints(DataFlow.All, DeviceState.All))
                {
                    try
                    {
                        if (device.FriendlyName.StartsWith(devices[i].Capabilities.ProductName))
                        {
                            devices[i].ProductName = device.FriendlyName;
                            break;
                        }
                    }
                    catch (COMException ex)
                    {
                        Debug.WriteLine(ex);
                    }
                }
            }

            return devices;
        }
    }
}

// References:
// [ComboBox: Adding Text and Value to an Item (no Binding Source)](https://stackoverflow.com/questions/3063320/combobox-adding-text-and-value-to-an-item-no-binding-source)
// [Get the full name of a waveIn device](https://stackoverflow.com/questions/1449162/get-the-full-name-of-a-wavein-device)
