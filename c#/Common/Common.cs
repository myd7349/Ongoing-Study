// 2016-03-03T15:17+08:00

using System;
using System.Diagnostics;
using System.IO;

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
    }
}

// References:
// [Func vs. Action vs. Predicate](http://stackoverflow.com/questions/4317479/func-vs-action-vs-predicate)
