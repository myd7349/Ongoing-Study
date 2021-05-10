namespace NLogBenchmark
{
    using NLog;

    using Common;

    class Program
    {
        private static Logger Logger = LogManager.GetCurrentClassLogger();

        private const int Count = 10000;

        private static void NaiveLogBench()
        {
            for (int i = 0; i < Count; ++i)
                NaiveLogger.Log("Hello, world!");
        }

        private static void NLogBench()
        {
            for (int i = 0; i < Count; ++i)
                Logger.Info("Hello, world!");
        }

        static void Main(string[] args)
        {
            Util.BenchmarkHelper("NaiveLog", NaiveLogBench, 1);
            Util.BenchmarkHelper("NLog", NLogBench, 1);

            Util.Pause();
        }
    }
}
