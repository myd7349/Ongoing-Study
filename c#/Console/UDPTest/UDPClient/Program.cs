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
            using (var clientSocket = new UdpClient(AddressFamily.InterNetwork))
            {
                Console.Write("Please input a sentence: ");
                var sentence = Console.ReadLine();

                var localHost = Dns.GetHostEntry("localhost");
                var serverHost = new IPEndPoint(localHost.AddressList[1].MapToIPv4(), 12000);
                var bytes = Encoding.UTF8.GetBytes(sentence);
                clientSocket.Send(bytes, bytes.Length, serverHost);

                try
                {
                    bytes = clientSocket.Receive(ref serverHost);
                    Console.WriteLine("Received from server: {0}", Encoding.UTF8.GetString(bytes));
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


// References:
// https://stackoverflow.com/questions/20038943/simple-udp-example-to-send-and-receive-data-from-same-socket
