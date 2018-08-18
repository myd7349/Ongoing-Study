// 2016-03-03T15:17+08:00

using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;

namespace Common
{
    public sealed class Util
    {
        [Conditional("DEBUG")]
        public static void Pause(string prompt = "Press any key to quit!")
        {
            Console.Write(prompt);
            Console.ReadKey();
        }

        public static Action PauseNul = () => Pause("");

        public static string GetProgName(string defaultName = "")
        {
            string progName = defaultName;

            var args = Environment.GetCommandLineArgs();
            if (args.Length >= 1)
            {
                progName = Path.GetFileNameWithoutExtension(args[0]);

                if (progName.EndsWith(".vshost"))
                    progName = Path.GetFileNameWithoutExtension(progName);
            }

            return progName;
        }

        public static string GetAppPath()
        {
            return Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
        }

        public static long Benchmark(Action action, int repeat)
        {
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            for (int i = 0; i < repeat; ++i)
                action();
            stopWatch.Stop();
            return stopWatch.ElapsedMilliseconds;
        }

        public static void BenchmarkHelper(string name, Action action, int repeat)
        {
            long elapsedMS = Benchmark(action, repeat);
            Console.WriteLine("Running for {0} times:\n{1}: {2}ms", repeat, name, elapsedMS);
        }
    }
}

// References:
// [Func vs. Action vs. Predicate](http://stackoverflow.com/questions/4317479/func-vs-action-vs-predicate)
// [OngoingStudy/c#/Console/GetApplicationPath]
// https://stackoverflow.com/questions/616584/how-do-i-get-the-name-of-the-current-executable-in-c
