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
                    using (var streamReader = new StreamReader(fileStream))
                    {
                        Cat(streamReader);
                    }
                }
            }
            else
            {
                using (var streamReader = new StreamReader(Console.OpenStandardInput(), Console.InputEncoding))
                {
                    Console.SetIn(streamReader);
                    Cat(streamReader);
                }
            }
        }

        private static void Cat(StreamReader streamReader)
        {
            string line = null;

            while ((line = streamReader.ReadLine()) != null)
                Console.WriteLine(line);
        }
    }
}


// References:
// [C# How to redirect stream to the console Out?](https://stackoverflow.com/questions/3127498/c-sharp-how-to-redirect-stream-to-the-console-out)
// [C# Console receive input with pipe](https://stackoverflow.com/questions/199528/c-sharp-console-receive-input-with-pipe)
// [Reading from Standard Input in C# [duplicate]](https://stackoverflow.com/questions/34888073/reading-from-standard-input-in-c-sharp)
