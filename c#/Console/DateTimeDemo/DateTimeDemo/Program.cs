namespace DateTimeDemo
{
    using static System.Console;

    using static Common.DateTimeHelper;
    using static Common.Util;

    class Program
    {
        static void Main(string[] args)
        {
            long calendarTime = 0;
            WriteLine($"time: {time(ref calendarTime)}");
            WriteLine($"Calendar time: {calendarTime}");
            WriteLine($"Time: {Time()}");

            var now = System.DateTime.Now;
            WriteLine($"Now: {now}");
            WriteLine($"UtcNow: {System.DateTime.UtcNow}");

            var unixTimeSeconds = DateTimeToUnixTimeSeconds(now);
            WriteLine($"DateTimeToUnixTimeSeconds: {unixTimeSeconds}");
            WriteLine($"UnixTimeSecondsToDateTime: {UnixTimeSecondsToDateTime(unixTimeSeconds)}");

            var unixTimeMilliseconds = DateTimeToUnixTimeMilliseconds(now);
            WriteLine($"DateTimeToUnixTimeMilliseconds: {unixTimeMilliseconds}");
            WriteLine($"UnixTimeMillisecondsToDateTime: {UnixTimeMillisecondsToDateTime(unixTimeMilliseconds)}");

            Pause();
        }
    }
}
