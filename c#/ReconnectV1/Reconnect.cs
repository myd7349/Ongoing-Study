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
            int dataPackSize = 19;
            var dataPack = new byte[dataPackSize];
            
            while (true)
            {
                try
                {
                    if (!serial.IsOpen)
                    {
                        serial.Open();
                        if (serial.IsOpen)
                            serial.Write(startCommand, 0, 2);
                        else
                            continue;
                    }

                    while (serial.Read(dataPack, 0, 1) == 1 && dataPack[0] != 0xc0) { }

                    if (serial.Read(dataPack, 1, dataPackSize - 1) == dataPackSize - 1)
                    {
                        Console.WriteLine("{0:x}", dataPack[0]);
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
