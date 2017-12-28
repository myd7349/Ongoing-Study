// 2017-12-28T15:01+08:00
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;


namespace UDPServer
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var serverSocket = new UdpClient(12000))
            {
                while (true)
                {
                    var remoteHost = new IPEndPoint(IPAddress.Any, 12000);
                    var bytes = serverSocket.Receive(ref remoteHost);
                    var sentence = Encoding.UTF8.GetString(bytes);

                    Console.WriteLine("Received [{0}] from [{1}].", sentence, remoteHost);

                    bytes = Encoding.UTF8.GetBytes(sentence.ToUpper());
                    serverSocket.Send(bytes, bytes.Length, remoteHost);
                }
            }
        }
    }
}


// References:
// https://stackoverflow.com/questions/20038943/simple-udp-example-to-send-and-receive-data-from-same-socket
