namespace Common
{
    using System;

    using System.Runtime.InteropServices;

    public static class DateTimeHelper
    {
        public static readonly DateTime Epoch = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);

        public static double Time()
        {
            return (DateTime.UtcNow - Epoch).TotalSeconds;
        }

        public static double DateTimeToUnixTimeSeconds(DateTime dateTime)
        {
            var dateTimeSpan = dateTime.ToUniversalTime() - Epoch;
            return dateTimeSpan.TotalSeconds;
        }

        public static double DateTimeToUnixTimeMilliseconds(DateTime dateTime)
        {
            var dateTimeSpan = dateTime.ToUniversalTime() - Epoch;
            return dateTimeSpan.TotalMilliseconds;
        }

        public static DateTime UnixTimeSecondsToDateTime(double calendarTime)
        {
            return Epoch.AddSeconds(calendarTime).ToLocalTime();
        }

        public static DateTime UnixTimeMillisecondsToDateTime(double milliseconds)
        {
            return Epoch.AddMilliseconds(milliseconds).ToLocalTime();
        }

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern long time(ref long arg);
    }
}


// References:
// https://stackoverflow.com/questions/7003373/how-to-get-datetime-now-in-yyyy-mm-ddthhmmsstzd-format-using-c-sharp
// [How do I get epoch time in C#?](https://stackoverflow.com/questions/9453101/how-do-i-get-epoch-time-in-c)
// [How do you convert epoch time in C#?](https://stackoverflow.com/questions/2883576/how-do-you-convert-epoch-time-in-c)
// [Get DateTime.Now with milliseconds precision](https://stackoverflow.com/questions/16032451/get-datetime-now-with-milliseconds-precision)
// [How can I convert a Unix timestamp to DateTime and vice versa?](https://stackoverflow.com/questions/249760/how-can-i-convert-a-unix-timestamp-to-datetime-and-vice-versa)
