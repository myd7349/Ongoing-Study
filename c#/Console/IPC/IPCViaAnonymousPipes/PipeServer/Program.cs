namespace PipeServer
{
    using System;
    using System.Diagnostics;
    using System.IO;
    using System.IO.Pipes;

    class Program
    {
        static void Main(string[] args)
        {
            string fileName;
            if (File.Exists("PipeClient.exe"))
                fileName = "PipeClient.exe";
            else
                fileName = "PipeClientCpp.exe";

            Process pipeClientProcess = new Process();
            pipeClientProcess.StartInfo.FileName = fileName;

            using (var pipeServer = new AnonymousPipeServerStream(
                PipeDirection.Out, HandleInheritability.Inheritable))
            {
                Console.WriteLine("[SERVER] Current TransmissionMode: {0}.", pipeServer.TransmissionMode);

                pipeClientProcess.StartInfo.Arguments = pipeServer.GetClientHandleAsString();
                pipeClientProcess.StartInfo.UseShellExecute = false;
                pipeClientProcess.Start();

                pipeServer.DisposeLocalCopyOfClientHandle();

                try
                {
                    using (var streamWriter = new StreamWriter(pipeServer))
                    {
                        streamWriter.AutoFlush = true;
                        streamWriter.WriteLine("SYNC");
                        pipeServer.WaitForPipeDrain();
                        Console.Write("[SERVER] Enter text: ");
                        streamWriter.WriteLine(Console.ReadLine());
                    }
                }
                catch (IOException e)
                {
                    Console.WriteLine("[SERVER] Error: {0}", e.Message);
                }
            }

            pipeClientProcess.WaitForExit();
            pipeClientProcess.Close();
            Console.WriteLine("[SERVER] Client quit. Server terminating.");

            Console.ReadKey();
        }
    }
}


// References:
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [How to remote invoke another process method from C# application](https://stackoverflow.com/questions/19999049/how-to-remote-invoke-another-process-method-from-c-sharp-application)
// [What is the simplest method of inter-process communication between 2 C# processes?](https://stackoverflow.com/questions/528652/what-is-the-simplest-method-of-inter-process-communication-between-2-c-sharp-pro)
// [How to: Use Anonymous Pipes for Local Interprocess Communication](https://docs.microsoft.com/en-us/dotnet/standard/io/how-to-use-anonymous-pipes-for-local-interprocess-communication)
