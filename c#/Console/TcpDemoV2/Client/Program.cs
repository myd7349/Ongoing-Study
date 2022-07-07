//#define USE_IPENDPOINT

using System.CommandLine;
using System.Net;
using System.Net.Sockets;

namespace Client
{
    class Program
    {
        static int Main(string[] args)
        {
            return BuildRootCommand().Invoke(args);
        }

        private static RootCommand BuildRootCommand()
        {
            var addressOption = new Option<string?>(
                new string[] { "--addr", "-a" },
                description: "IP address.");

            var portOption = new Option<int>(
                new[] { "--port", "-p" },
                description: "Port number.")
            {
                IsRequired = true,
            };

            var fileOption = new Option<FileInfo>(
                new[] { "--file", "-f" },
                description: "Input file path.")
            {
                IsRequired = true,
            };

            var delayOption = new Option<int?>(
                name: "--delay",
                description: "Delay(milliseconds).");

            var debugOption = new Option<bool>(
                new[] { "--debug", "-d" },
                description: "Enable debug mode.");

            var rootCommand = new RootCommand
            {
                addressOption,
                portOption,
                fileOption,
                delayOption,
                debugOption,
            };
            rootCommand.Description = "A simple TCP client.";
            rootCommand.SetHandler(
                RunClient,
                addressOption,
                portOption,
                fileOption,
                delayOption,
                debugOption);

            return rootCommand;
        }

        private static void RunClient(string? address, int port, FileInfo file, int? delay, bool debug)
        {
            if (debug)
                Console.WriteLine($"[DEBUG] Address: {address}\nPort: {port}\nFile: {file}");

#if USE_IPENDPOINT
            IPAddress? ipAddress;
            if (!string.IsNullOrEmpty(address))
            {
                if (!IPAddress.TryParse(address, out ipAddress))
                {
                    Console.WriteLine($"Invalid IP address: {address}.");
                    return;
                }
            }
            else
            {
                var hostName = Dns.GetHostName();
                var hostEntry = Dns.GetHostEntry(hostName);
                ipAddress = hostEntry.AddressList.FirstOrDefault();

                if (debug)
                {
                    Console.WriteLine($"[DEBUG] Host name: {hostName}.");
                    Console.WriteLine($"[DEBUG] Host address: {ipAddress}.");
                }
            }
#endif

            if (port < IPEndPoint.MinPort || port > IPEndPoint.MaxPort)
            {
                Console.WriteLine($"Port number out of range: [{IPEndPoint.MinPort}, {IPEndPoint.MaxPort}].");
                return;
            }

            if (!file.Exists)
            {
                Console.WriteLine($"File \"{file}\" doesn't exist.");
                return;
            }

            using var fileStream = File.OpenRead(file.FullName);

#if USE_IPENDPOINT
            var ipEndPoint = new IPEndPoint(ipAddress ?? IPAddress.Any, port);
            // Call Bind instead of Connect.
            using var client = new TcpClient(ipEndPoint);
#else
            // Connect
            using var client = new TcpClient(address ?? Dns.GetHostName(), port);
#endif

            using var clientStream = client.GetStream();

            var buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = fileStream.Read(buffer, 0, buffer.Length)) > 0)
            {
                clientStream.Write(buffer, 0, bytesRead);

                if (delay > 0)
                    Thread.Sleep(delay.Value);
            }
        }
    }
}


// References:
// [System.CommandLine overview](https://learn.microsoft.com/en-us/dotnet/standard/commandline/)
// [How to handle termination in System.CommandLine](https://learn.microsoft.com/en-us/dotnet/standard/commandline/handle-termination)
// [TCP overview](https://learn.microsoft.com/en-us/dotnet/fundamentals/networking/sockets/tcp-classes)
// [TcpClient Class](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.tcpclient?view=net-6.0)
