namespace ThreadGo
{
    using System;
    using System.Diagnostics;
    using System.IO;
    using System.Reflection;

    class Program
    {
        static void Go(string appPath)
        {
            Console.Write("Run {0}: ", Path.GetFileNameWithoutExtension(appPath));

            uint counter = 0;
            var stopwatch = new Stopwatch();

            while (true)
            {
                counter++;
                if (counter == uint.MaxValue)
                {
                    Console.WriteLine("I quit!");
                    break;
                }

                using (var process = new Process())
                {
                    process.StartInfo.UseShellExecute = false;
                    process.StartInfo.FileName = appPath;
                    process.StartInfo.CreateNoWindow = true;
                    process.StartInfo.RedirectStandardOutput = true;

                    process.Start();

                    var output = process.StandardOutput.ReadToEnd();
                    if (output == "DoneDone")
                    {
                        Console.WriteLine("#{0} we got \"DoneDone\"! It takes {1} ms.", counter, stopwatch.ElapsedMilliseconds);
                        break;
                    }
                }
            }
        }

        static void Main()
        {
            var appPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);

            Go(Path.Combine(appPath, "GoV3.exe"));
            Go(Path.Combine(appPath, "GoV2.exe"));
            Go(Path.Combine(appPath, "GoV1.exe"));

            Console.ReadKey();
        }
    }
}

// References:
// https://stackoverflow.com/questions/181719/how-do-i-start-a-process-from-c
