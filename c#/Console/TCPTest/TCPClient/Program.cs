// 2017-12-27T12:13+08:00
using System;
using System.Net.Sockets;
using System.Text;

using Common;

namespace TCPClient
{
    class Program
    {
        static void Main(string[] args)
        {
#if false
            using (var clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                try
                {
                    clientSocket.Connect("localhost", 12001);

                    const int BufferSize = 1024;
                    var buffer = new byte[BufferSize];

                    Console.Write("Input a sentence: ");
                    var sentence = Console.ReadLine().TrimEnd('\r', '\n');
                    clientSocket.Send(Encoding.UTF8.GetBytes(sentence));

                    var receivedBytes = clientSocket.Receive(buffer);
                    Console.WriteLine("Received from server: {0}", Encoding.UTF8.GetString(buffer, 0, receivedBytes));
                }
                catch (SocketException ex)
                {
                    Console.WriteLine(ex);
                }
            }
#else
            // In corefx source code:
            // TCPClient.cs:
            // The System.Net.Sockets.TcpClient class provide TCP services at a higher level
            // of abstraction than the System.Net.Sockets.Socket class. System.Net.Sockets.TcpClient
            // is used to create a Client connection to a remote host.
            // UDPClient.cs:
            // The System.Net.Sockets.UdpClient class provides access to UDP services at a higher abstraction
            // level than the System.Net.Sockets.Socket class. System.Net.Sockets.UdpClient is used to
            // connect to a remote host and to receive connections from a remote client.

            using (var clientSocket = new TcpClient(AddressFamily.InterNetwork))
            {
                try
                {
                    clientSocket.Connect("localhost", 12001);

                    const int BufferSize = 1024;
                    var buffer = new byte[BufferSize];

                    Console.Write("Input a sentence: ");
                    var sentence = Console.ReadLine().TrimEnd('\r', '\n');
                    var bytes = Encoding.UTF8.GetBytes(sentence);
                    clientSocket.GetStream().Write(bytes, 0, bytes.Length);

                    var receivedBytes = clientSocket.GetStream().Read(buffer, 0, buffer.Length);
                    Console.WriteLine("Received from server: {0}", Encoding.UTF8.GetString(buffer, 0, receivedBytes));
                }
                catch (SocketException ex)
                {
                    Console.WriteLine(ex);
                }
            }
#endif

            Util.Pause();
        }
    }
}


// References:
// Computer Networking: A Top-Down Approach 5th Edition, 2.7
