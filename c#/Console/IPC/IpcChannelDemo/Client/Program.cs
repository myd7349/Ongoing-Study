namespace Client
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
            var channel = new IpcChannel();

            ChannelServices.RegisterChannel(channel, false);

            var remoteType = new WellKnownClientTypeEntry(
                typeof(RemoteObject),
                "ipc://localhost:9090/RemoteObject.rem");
            RemotingConfiguration.RegisterWellKnownClientType(remoteType);

            // Create a message sink
            string objectUri;
            var messageSink = channel.CreateMessageSink(
                "ipc://localhost:9090/RemoteObject.rem",
                null,
                out objectUri);
            Console.WriteLine("The URI of the message sink is {0}.", objectUri);
            if (messageSink != null)
            {
                Console.WriteLine("The type of the message sink is {0}.",
                    messageSink.GetType().ToString());
            }

            // Create an instance of the remote object.
            var service = new RemoteObject();
            // Invoke a method on the remote object.
            Console.WriteLine("The client is invoking the remote object.");
            Console.WriteLine("The remote object has been called {0} times.", service.GetCount());

            Console.ReadKey();
        }
    }
}


// References:
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [How to remote invoke another process method from C# application](https://stackoverflow.com/questions/19999049/how-to-remote-invoke-another-process-method-from-c-sharp-application)
// [What is the easiest way to do inter process communication in C#?](https://stackoverflow.com/questions/1802475/what-is-the-easiest-way-to-do-inter-process-communication-in-c)
// [IpcChannel Class](https://docs.microsoft.com/en-us/dotnet/api/system.runtime.remoting.channels.ipc.ipcchannel?redirectedfrom=MSDN&view=netframework-4.8)
