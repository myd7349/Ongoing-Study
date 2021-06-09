namespace ThreadYieldProfile
{
    using System;
    using System.Diagnostics;
    using System.Runtime.InteropServices;
    using System.Threading;

    class Program
    {
        static void Main()
        {
            Profile(() => SwitchToThread());
            Profile(() => Thread.Sleep(0));
            Profile(() => Thread.Sleep(1));
            Profile(() =>
            {
                timeBeginPeriod(1);
                Thread.Sleep(1);
                timeEndPeriod(1);
            });
            Profile(() => Thread.Yield());
            Profile(() => Thread.SpinWait(1));

            Console.WriteLine("Press any key to quit.");
            Console.ReadKey();
        }

        static void Profile(Action func)
        {
            var stopwatch = new Stopwatch();
            var beginTime = DateTime.Now;
            ulong count = 0;

            while (DateTime.Now.Subtract(beginTime).TotalSeconds < 5)
            {
                stopwatch.Start();
                func();
                stopwatch.Stop();
                count++;
            }

            Console.WriteLine($"Made {count} iterations in ~5s. Total sleep time {stopwatch.ElapsedMilliseconds}[ms]. Mean time = {stopwatch.ElapsedMilliseconds / (double)count} [ms]");
        }

        [DllImport("kernel32.dll")]
        static extern bool SwitchToThread();

        [DllImport("winmm.dll")]
        internal static extern uint timeBeginPeriod(uint period);

        [DllImport("winmm.dll")]
        internal static extern uint timeEndPeriod(uint period);
    }
}

// References:
// [SwitchToThread/Thread.Yield vs.Thread.Sleep(0) vs.Thead.Sleep(1)](https://stackoverflow.com/questions/1413630/switchtothread-thread-yield-vs-thread-sleep0-vs-thead-sleep1)
// [Thread.Sleep(0) vs Sleep(1) vs Yeild](https://www.cnblogs.com/stg609/p/3857242.html)
