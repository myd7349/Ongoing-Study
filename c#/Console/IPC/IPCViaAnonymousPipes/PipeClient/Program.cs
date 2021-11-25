namespace PipeClient
{
    using System;
    using System.IO;
    using System.IO.Pipes;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
                return;

            using (var pipeClient = new AnonymousPipeClientStream(
                PipeDirection.In, args[0]))
            {
                Console.WriteLine("[CLIENT] Current TransmissionMode: {0}.",
                   pipeClient.TransmissionMode);

                using (var streamReader = new StreamReader(pipeClient))
                {
                    string message;

                    do
                    {
                        Console.WriteLine("[CLIENT] Wait for SYNC...");
                        message = streamReader.ReadLine();
                    }
                    while (!message.StartsWith("SYNC"));

                    while ((message = streamReader.ReadLine()) != null)
                    {
                        Console.WriteLine("[CLIENT] Echo: {0}", message);
                    }
                }
            }

            Console.Write("[CLIENT] Press Enter to continue...");
            Console.ReadLine();
        }
    }
}


// References:
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [How to remote invoke another process method from C# application](https://stackoverflow.com/questions/19999049/how-to-remote-invoke-another-process-method-from-c-sharp-application)
// [What is the simplest method of inter-process communication between 2 C# processes?](https://stackoverflow.com/questions/528652/what-is-the-simplest-method-of-inter-process-communication-between-2-c-sharp-pro)
// [How to: Use Anonymous Pipes for Local Interprocess Communication](https://docs.microsoft.com/en-us/dotnet/standard/io/how-to-use-anonymous-pipes-for-local-interprocess-communication)
// https://github.com/rocksdanister/lively/tree/dev-v1.0-fluent-netcore/src/livelywpf/livelyCmdUtility/IPC
