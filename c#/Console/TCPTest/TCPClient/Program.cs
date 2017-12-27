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

            Util.Pause();
        }
    }
}


// References:
// Computer Networking: A Top-Down Approach 5th Edition, 2.7
