namespace Common
{
    using System;
    using System.IO;
    using System.IO.Ports;

    public class SerialPortEx : SerialPort
    {
        public SerialPortEx()
            : base()
        {
        }

        public SerialPortEx(string portName)
            : base(portName)
        {
        }

        public SerialPortEx(string portName, int baudRate)
            : base(portName, baudRate)
        {
        }

        public SerialPortEx(string portName, int baudRate, Parity parity)
            : base(portName, baudRate, parity)
        {
        }

        public SerialPortEx(string portName, int baudRate, Parity parity, int dataBits)
            : base(portName, baudRate, parity, dataBits)
        {
        }

        public SerialPortEx(string portName, int baudRate, Parity parity, int dataBits, StopBits stopBits)
            : base(portName, baudRate, parity, dataBits, stopBits)
        {
        }

        public new void Open()
        {
            try
            {
                base.Open();
                baseStream_ = BaseStream;
                GC.SuppressFinalize(BaseStream);
            }
            catch
            {
            }
        }

        public new void Dispose()
        {
            Dispose(true);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (base.Container != null))
            {
                base.Container.Dispose();
            }

            try
            {
                if (baseStream_.CanRead)
                {
                    baseStream_.Close();
                    GC.ReRegisterForFinalize(baseStream_);
                }
            }
            catch
            {
                // ignore exception - bug with USB - serial adapters.
            }

            base.Dispose(disposing);
        }

        private Stream baseStream_;
    }
}

// References:
// [How can my application recover when a USB emulated serial port vanishes and reappears?](https://stackoverflow.com/questions/37777626/how-can-my-application-recover-when-a-usb-emulated-serial-port-vanishes-and-reap)
// [Using RegisterDeviceNotification in a.NET app](https://stackoverflow.com/questions/1976573/using-registerdevicenotification-in-a-net-app)
// [Detecting when a SerialPort gets disconnected](https://stackoverflow.com/questions/13408476/detecting-when-a-serialport-gets-disconnected)
