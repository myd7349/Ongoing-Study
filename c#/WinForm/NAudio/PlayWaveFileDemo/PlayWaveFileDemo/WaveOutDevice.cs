namespace PlayWaveFileDemo
{
    using NAudio.Wave;

    public class WaveOutDevice
    {
        public WaveOutDevice(int deviceNumber, WaveOutCapabilities capabilities)
        {
            DeviceNumber = deviceNumber;
            Capabilities = capabilities;
        }

        public override string ToString()
        {
            return string.Format("#{0}: {1}", DeviceNumber, Capabilities.ProductName);
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
    }
}

// References:
// [ComboBox: Adding Text and Value to an Item (no Binding Source)](https://stackoverflow.com/questions/3063320/combobox-adding-text-and-value-to-an-item-no-binding-source)
