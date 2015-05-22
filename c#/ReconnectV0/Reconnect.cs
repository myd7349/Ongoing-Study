// 2015-05-22T08:46+08:00
using System;
using System.IO.Ports;
using System.Threading;

namespace SerialPortsTest
{
    static partial class Reconnect
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: reconnect port");
                return;
            }

            var serial = new SerialPort(args[0], 576000);
            var startCommand = new byte[] { 0xAA, 0xAA };
            var stopCommand = new byte[] { 0xBB, 0xBB };
            var getVerCommand = new byte[] { 0xCC, 0xCC };
            var version = new byte[3];

            while (true)
            {
                try
                {
                    if (!serial.IsOpen)
                    {
                        serial.Open();
                    }
                    else
                    {
                        serial.Write(getVerCommand, 0, 2);

                        // *** Comment out/Uncomment this line, and see how the behaviour of 
                        // this program changes.
                        //Thread.Sleep(200);

                        if (serial.Read(version, 0, 3) == 3 && version[0] == 0x50)
                        {
                            Console.WriteLine("{0:x} {1:x} {2:x}", version[0], version[1], version[2]);
                        }
                    }
                }
                catch
                {
                    Console.WriteLine("Oops!");
                }

                Thread.Sleep(200);
            }
        }
    }
}
