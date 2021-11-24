namespace Server
{
    using System;
    using System.Runtime.Remoting;
    using System.Runtime.Remoting.Channels;
    using System.Runtime.Remoting.Channels.Ipc;
    using System.Security.Permissions;

    using Common;

    class Program
    {
        [SecurityPermission(SecurityAction.Demand)]
        static void Main(string[] args)
        {
            var serverChannel = new IpcChannel("localhost:9090");
            ChannelServices.RegisterChannel(serverChannel, false);

            Console.WriteLine("The name of the channel is {0}.", serverChannel.ChannelName);
            Console.WriteLine("The priority of the channel is {0}.", serverChannel.ChannelPriority);

            var channelData = serverChannel.ChannelData as ChannelDataStore;
            foreach (var uri in channelData.ChannelUris)
                Console.WriteLine("The channel URI is {0}.", uri);

            RemotingConfiguration.RegisterWellKnownServiceType(
                typeof(RemoteObject), "RemoteObject.rem",
                WellKnownObjectMode.Singleton);

            var urls = serverChannel.GetUrlsForUri("RemoteObject.rem");
            if (urls.Length > 0)
            {
                var objectUrl = urls[0];
                string objectUri;
                var channelUri = serverChannel.Parse(objectUrl, out objectUri);

                Console.WriteLine("The object URI is {0}.", objectUri);
                Console.WriteLine("The channel URI is {0}.", channelUri);
                Console.WriteLine("The object URL is {0}.", objectUrl);
            }

            // Wait for the user prompt.
            Console.WriteLine("Press ENTER to exit the server.");
            Console.ReadLine();
            Console.WriteLine("The server is exiting.");
        }
    }
}


// References:
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [How to remote invoke another process method from C# application](https://stackoverflow.com/questions/19999049/how-to-remote-invoke-another-process-method-from-c-sharp-application)
// [What is the easiest way to do inter process communication in C#?](https://stackoverflow.com/questions/1802475/what-is-the-easiest-way-to-do-inter-process-communication-in-c)
// [IpcChannel Class](https://docs.microsoft.com/en-us/dotnet/api/system.runtime.remoting.channels.ipc.ipcchannel?redirectedfrom=MSDN&view=netframework-4.8)
