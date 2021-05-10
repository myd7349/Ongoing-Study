namespace AccurateTimerDemo
{
    using System;
    using System.Diagnostics;
    using System.Threading;

    using Common;

    class Program
    {
        static void Main(string[] args)
        {
            var stopwatch = Stopwatch.StartNew();
            int count = 0;
            const int MaxCount = 20;

            var timer = new Timer(
                _ =>
                {
                    Console.WriteLine("Ellapsed ms: {0}", stopwatch.ElapsedMilliseconds);
                    Interlocked.Increment(ref count);
                },
                null,
                1000,
                100);

            while (true)
            {
                if (Thread.VolatileRead(ref count) >= MaxCount)
                {
                    timer.Dispose();
                    break;
                }
            }

            Console.WriteLine("---------- MMTimer ----------");
            count = 0;
            stopwatch.Restart();

            var mmTimer = new MMTimer(
                _ =>
                {
                    Console.WriteLine("Ellapsed ms: {0}", stopwatch.ElapsedMilliseconds);
                    Interlocked.Increment(ref count);
                }
                )
            {
                Interval = 100
            };
            mmTimer.Start();

            while (true)
            {
                if (Thread.VolatileRead(ref count) >= MaxCount)
                {
                    mmTimer.Stop();
                    break;
                }
            }

            Util.Pause();
        }
    }
}

// References:
// https://stackoverflow.com/questions/4563704/c-sharp-how-do-you-stop-a-timer
// https://stackoverflow.com/questions/15495459/using-interlocked-compareexchange-to-increment-a-counter-until-a-value
// https://stackoverflow.com/questions/2515975/problem-with-waitable-timers-in-windows-timesetevent-and-createtimerqueuetimer
