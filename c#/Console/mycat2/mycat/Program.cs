namespace mycat
{
    using System;
    using System.IO;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                foreach (var arg in args)
                {
                    using (var fileStream = File.OpenRead(arg))
                        Cat(fileStream);
                }
            }
            else
            {
                Cat(Console.OpenStandardInput());
            }
        }

        private static void Cat(Stream stream)
        {
            stream.CopyTo(Console.OpenStandardOutput());
        }
    }
}


// References:
// [C# How to redirect stream to the console Out?](https://stackoverflow.com/questions/3127498/c-sharp-how-to-redirect-stream-to-the-console-out)
// [C# Console receive input with pipe](https://stackoverflow.com/questions/199528/c-sharp-console-receive-input-with-pipe)
// [Reading from Standard Input in C# [duplicate]](https://stackoverflow.com/questions/34888073/reading-from-standard-input-in-c-sharp)
// [Console.OpenStandardOutput Method](https://docs.microsoft.com/en-us/dotnet/api/system.console.openstandardoutput?view=net-5.0)
