// 2017-12-27T12:23+08:00
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;


namespace TCPServer
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                serverSocket.Bind(new IPEndPoint(IPAddress.Any, 12001));
                serverSocket.Listen(1);

                const int BufferSize = 1024;
                var buffer = new byte[BufferSize];

                while (true)
                {
                    var connectionSocket = serverSocket.Accept();
                    var receivedBytes = connectionSocket.Receive(buffer);

                    var sentence = Encoding.UTF8.GetString(buffer, 0, receivedBytes);
                    Console.WriteLine("Received [{0}] from [{1}]", sentence, connectionSocket.RemoteEndPoint);

                    connectionSocket.Send(Encoding.UTF8.GetBytes(sentence.ToUpper()));
                    connectionSocket.Close();
                }
            }
        }
    }
}


// References:
// Computer Networking: A Top-Down Approach 5th Edition, 2.7
// [TcpListener Class](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.tcplistener?view=net-6.0)
