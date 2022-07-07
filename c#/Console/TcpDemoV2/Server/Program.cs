using System.CommandLine;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;

namespace Server
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

            var timeoutOption = new Option<int?>(
                new[] { "--timeout", "-t" },
                description: "Read timeout(milliseconds).");

            var fileOption = new Option<FileInfo>(
                new[] { "--file", "-f" },
                description: "Input file path.")
            {
                IsRequired = true,
            };

            var debugOption = new Option<bool>(
                new[] { "--debug", "-d" },
                description: "Enable debug mode.");

            var rootCommand = new RootCommand
            {
                addressOption,
                portOption,
                timeoutOption,
                fileOption,
                debugOption,
            };
            rootCommand.Description = "A simple TCP server.";
            rootCommand.SetHandler(
                RunServer,
                addressOption,
                portOption,
                timeoutOption,
                fileOption,
                debugOption);

            return rootCommand;
        }

        private static void RunServer(string? address, int port, int? timeout, FileInfo file, bool debug)
        {
            if (debug)
                Console.WriteLine($"[DEBUG] Address: {address}\nPort: {port}\nTimeout: {timeout}\nFile: {file}");

            IPAddress? ipAddress = null;
            if (!string.IsNullOrEmpty(address))
            {
                if (!IPAddress.TryParse(address, out ipAddress))
                {
                    Console.WriteLine($"Invalid IP address: {address}.");
                    return;
                }
            }

            if (port < IPEndPoint.MinPort || port > IPEndPoint.MaxPort)
            {
                Console.WriteLine($"Port number out of range: [{IPEndPoint.MinPort}, {IPEndPoint.MaxPort}].");
                return;
            }

            IPEndPoint ipEndPoint;
            if (ipAddress != null)
                ipEndPoint = new IPEndPoint(ipAddress, port);
            else
                ipEndPoint = new IPEndPoint(IPAddress.Any, port);

            var server = new TcpListener(ipEndPoint);

            try
            {
                server.Start();

                using (var client = server.AcceptTcpClient())
                using (var fileStream = File.Create(file.FullName))
                {
                    var stream = client.GetStream();

                    var timeoutSet = false;

                    var buffer = new byte[4096];
                    int bytesRead;
                    long totalBytesRead = 0;

                    if (debug)
                        Console.WriteLine("[DEBUG] Start reading...");

                    var stopwatch = Stopwatch.StartNew();

                    while ((bytesRead = stream.Read(buffer, 0, buffer.Length)) != 0)
                    {
                        if (!timeoutSet)
                        {
                            if (timeout > 0)
                            {
                                stream.ReadTimeout = timeout.Value;

                                if (debug)
                                    Console.WriteLine($"[DEBUG] Set read timeout: {timeout.Value}ms.");
                            }

                            timeoutSet = true;
                        }

                        if (debug)
                            Console.WriteLine($"[DEBUG] Buffer size: {buffer.Length}, bytes read: {bytesRead}.");

                        fileStream.Write(buffer, 0, bytesRead);

                        totalBytesRead += bytesRead;
                    }

                    Console.WriteLine($"It took {stopwatch.ElapsedMilliseconds}ms to receive {totalBytesRead} bytes.");
                }
            }
            finally
            {
                server.Stop();
            }
        }
    }
}


// References:
// [System.CommandLine overview](https://learn.microsoft.com/en-us/dotnet/standard/commandline/)
// [How to handle termination in System.CommandLine](https://learn.microsoft.com/en-us/dotnet/standard/commandline/handle-termination)
