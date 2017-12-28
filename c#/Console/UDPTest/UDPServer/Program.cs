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
            using (var serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp))
            {
                serverSocket.Bind(new IPEndPoint(IPAddress.Any, 12000));

                const int BufferLength = 1024;
                var buffer = new byte[BufferLength];

                while (true)
                {
                    var byteCount = serverSocket.Receive(buffer);
                    var sentence = Encoding.UTF8.GetString(buffer, 0, byteCount);

                    Console.WriteLine("Received [{0}] from [{1}].", sentence, serverSocket.RemoteEndPoint);

                    serverSocket.SendTo(Encoding.UTF8.GetBytes(sentence.ToUpper()), serverSocket.RemoteEndPoint);
                }
            }
        }
    }
}
