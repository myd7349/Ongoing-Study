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
#if false
            using (var serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp))
            {
                serverSocket.Bind(new IPEndPoint(IPAddress.Any, 12000));

                const int BufferLength = 1024;
                var buffer = new byte[BufferLength];

                while (true)
                {
                    EndPoint clientHost = new IPEndPoint(IPAddress.Any, 12000);
                    var byteCount = serverSocket.ReceiveFrom(buffer, ref clientHost);
                    var sentence = Encoding.UTF8.GetString(buffer, 0, byteCount);

                    Console.WriteLine("Received [{0}] from [{1}].", sentence, clientHost);

                    serverSocket.SendTo(Encoding.UTF8.GetBytes(sentence.ToUpper()), clientHost);
                }
            }
#else
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
#endif
        }
    }
}


// References:
// https://stackoverflow.com/questions/20038943/simple-udp-example-to-send-and-receive-data-from-same-socket
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Net.Sockets/src/System/Net/Sockets/UDPClient.cs
