// 2016-03-03T15:17+08:00

using System;

namespace Common
{
    public sealed class Common
    {
        public static void Pause(string prompt = "Press any key to quit!")
        {
            Console.Write(prompt);
            Console.ReadKey();
        }

        public static Action PauseNul = () => Pause("");
    }
}
