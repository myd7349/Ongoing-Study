using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;

namespace Common
{
    public static class NetworkHelper
    {
        public static List<IPAddress> GetIPAddresses(AddressFamily? addressFamily = null)
        {
            // IPAddressCollection?
            var addresses = new List<IPAddress>();

            foreach (var netInterface in NetworkInterface.GetAllNetworkInterfaces())
            {
                Debug.WriteLine("Name: " + netInterface.Name);
                Debug.WriteLine("Description: " + netInterface.Description);
                Debug.WriteLine("Addresses: ");

                var ipProperties = netInterface.GetIPProperties();
                foreach (var addressInformation in ipProperties.UnicastAddresses)
                {
                    var address = addressInformation.Address;
                    if (addressFamily == null || addressFamily == AddressFamily.Unspecified)
                        addresses.Add(address);
                    else if (address.AddressFamily == addressFamily)
                        addresses.Add(address);

                    Debug.WriteLine(" " + address.ToString());
                }

                Debug.WriteLine("");
            }

            return addresses;
        }

        public static IPEndPoint ParseIPv4EndPoint(string endPoint)
        {
            if (string.IsNullOrEmpty(endPoint))
                throw new ArgumentException(nameof(endPoint));
            
            var parts = endPoint.Split(':');
            if (parts.Length != 2)
                throw new ArgumentException("Invalid IPv4 EndPoint.");

            if (!IPAddress.TryParse(parts[0], out var ipAddress))
                throw new ArgumentException($"Invalid IPv4 address: {parts[0]}.");

            if (!int.TryParse(parts[1], out var port))
                throw new ArgumentException($"Invalid port number: {parts[1]}.");

            return new IPEndPoint(ipAddress, port);
        }

        public static void ParseEndPoint(string endPoint, out IPAddress address, out int port)
        {
            if (string.IsNullOrEmpty(endPoint))
                throw new ArgumentException(nameof(endPoint));

            var parts = endPoint.Split(':');
            if (parts.Length < 2)
                throw new ArgumentException("Invalid IPEndPoint.");

            if (parts.Length == 2)
            {
                if (!IPAddress.TryParse(parts[0], out address))
                    throw new ArgumentException($"Invalid IPv4 address: {parts[0]}.");
            }
            else
            {
                var addressString = string.Join(":", parts, 0, parts.Length - 1);
                if (!IPAddress.TryParse(addressString, out address))
                    throw new ArgumentException($"Invalid IP address: {addressString}.");
            }
            
            if (!int.TryParse(parts[parts.Length - 1], NumberStyles.None, NumberFormatInfo.CurrentInfo, out port))
                throw new ArgumentException($"Invalid port number: {parts[1]}.");
        }

        public static IPEndPoint ParseEndPoint(string endPoint)
        {
            IPAddress address;
            int port;

            ParseEndPoint(endPoint, out address, out port);

            return new IPEndPoint(address, port);
        }

        public static bool IsValidIPv4Address(string address)
        {
            if (string.IsNullOrEmpty(address))
                return false;

            IPAddress ipAddress;
            return IPAddress.TryParse(address, out ipAddress) &&
                ipAddress.AddressFamily == AddressFamily.InterNetwork;
        }

        public static bool IsValidPort(string port)
        {
            if (string.IsNullOrEmpty(port))
                return false;

            int portInteger;
            return int.TryParse(port, out portInteger) &&
                IsValidPort(portInteger);
        }

        // https://github.com/dotnet/runtime/blob/main/src/libraries/Common/src/System/Net/TcpValidationHelpers.cs
        public static bool IsValidPort(int port)
        {
            return port >= IPEndPoint.MinPort && port <= IPEndPoint.MaxPort;
        }

        // void async OnStart()
        // {
        //     server.Start();
        //
        //     var client = await Task.Run(() => server.AcceptTcpClient(TimeSpan.FromSeconds(10))); // ObjectDisposedException
        // }
        //
        // void OnClose()
        // {
        //     server.Stop();
        // }
        //
        // 
        public static TcpClient AcceptTcpClient(this TcpListener tcpListener, TimeSpan timeOut)
        {
            if (tcpListener == null)
                throw new ArgumentNullException(nameof(tcpListener));

            var listenList = new ArrayList { tcpListener.Server };
            Socket.Select(listenList, null, null, (int)(timeOut.TotalMilliseconds * 1000));

            if (listenList.Contains(tcpListener.Server))
                return tcpListener.AcceptTcpClient();

            return null;
        }

        public static int ReadBytes(this NetworkStream networkStream, byte[] buffer, int offset, int count)
        {
            if (networkStream == null)
                throw new ArgumentNullException(nameof(networkStream));

            if (!networkStream.CanRead)
                throw new InvalidOperationException("NetworkStream can not be read.");

            ArrayHelper.ValidateArray(buffer, offset, count);

            int bytesRead = 0;

            while (bytesRead != count)
            {
                int bytesReadThisTime = networkStream.Read(buffer, offset, count - bytesRead);
                if (bytesReadThisTime == 0) // Socket is closed.
                    break;
                
                bytesRead += bytesReadThisTime;
                offset += bytesReadThisTime;
            }

            return count;
        }

        public static void StartNCPA()
        {
            var processStartInfo = new ProcessStartInfo();
            processStartInfo.FileName = "ncpa.cpl";
            processStartInfo.UseShellExecute = true;

            Process.Start(processStartInfo);
        }
    }
}


// References:
// [Best way to create IPEndpoint from string](https://stackoverflow.com/questions/2727609/best-way-to-create-ipendpoint-from-string)
// [Get All IP Addresses on Machine](https://stackoverflow.com/questions/5271724/get-all-ip-addresses-on-machine)
// https://github.com/lduchosal/ipnetwork
// [TcpListener Timeout/about/something? Without ASync?](https://stackoverflow.com/questions/3313313/tcplistener-timeout-about-something-without-async)
// [Socket.Select Method](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.socket.select?view=net-6.0)
// [IPAddress Class](https://learn.microsoft.com/en-us/dotnet/api/system.net.ipaddress?view=net-6.0)
// [TcpListener: how to stop listening while awaiting AcceptTcpClientAsync()?](https://stackoverflow.com/questions/19220957/tcplistener-how-to-stop-listening-while-awaiting-accepttcpclientasync)
// [Asynchronously wait for Task<T> to complete with timeout](https://stackoverflow.com/questions/4238345/asynchronously-wait-for-taskt-to-complete-with-timeout)
// [How do I interrupt Socket.Select](https://stackoverflow.com/questions/26290117/how-do-i-interrupt-socket-select)
// [Socket.Select Method](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.socket.select?view=net-6.0)
// > Use the Poll method if you only want to determine the status of a single Socket.
// [Socket Class](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.socket?view=net-6.0)
// >     // Send the request.
// >     // For the tiny amount of data in this example, the first call to Send() will likely deliver the buffer completely,
// >     // however this is not guaranteed to happen for larger real-life buffers.
// >     // The best practice is to iterate until all the data is sent.
// >     int bytesSent = 0;
// >     while (bytesSent < requestBytes.Length)
// >     {
// >         bytesSent += socket.Send(requestBytes, bytesSent, requestBytes.Length - bytesSent, SocketFlags.None);
// >     }
// [How to open "Network Connections" window programmatically](https://stackoverflow.com/questions/5032667/how-to-open-network-connections-window-programmatically)
// [Best way to programmatically configure network adapters in .NET](https://stackoverflow.com/questions/689230/best-way-to-programmatically-configure-network-adapters-in-net)
