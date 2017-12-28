// 2017-12-28T15:01+08:00
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

using Common;


namespace UDPClient
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp))
            {
                Console.Write("Please input a sentence: ");
                var sentence = Console.ReadLine();

                var localHost = Dns.GetHostEntry("localhost");
                var serverHost = new IPEndPoint(localHost.AddressList[1].MapToIPv4(), 12000);
                clientSocket.SendTo(Encoding.UTF8.GetBytes(sentence), serverHost);

                const int BufferLength = 1024;
                var buffer = new byte[BufferLength];

                try
                {
                    var byteCount = clientSocket.Receive(buffer);
                    Console.WriteLine("Received from server: {0}", Encoding.UTF8.GetString(buffer, 0, byteCount));
                }
                catch (SocketException ex)
                {
                    Console.WriteLine(ex);
                }
            }

            Util.Pause();
        }
    }
}
