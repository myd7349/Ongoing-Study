namespace NLogBenchmark
{
    using System;
    using System.IO;

    public static class NaiveLogger
    {
        public static readonly string LogFilePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Naive.log");

        public static void Log(string message)
        {
            if (message == null)
                return;

            var log = DateTime.Now.ToString("G"); // or ToString("yyyy-MM-ddTHH:mm:ss.fff")
            if (message != string.Empty)
                log += " " + message;
            log += '\n';

            File.AppendAllText(LogFilePath, log);
        }

        public static void Log(string format, params object[] args)
        {
            Log(string.Format(format, args));
        }
    }
}
