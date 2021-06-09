<Query Kind="Statements" />

Console.WriteLine(DateTime.Now.ToString("yyyy-MM-ddTHH:mm:sszzz"));
Console.WriteLine(DateTime.Now.ToString("G"));
Console.WriteLine(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff"));

Console.WriteLine("---------------------------------------- Standard formats ----------------------------------------");
// Not OK:
//var standardFormats = {"d", "D", "f", "F", "g", "G", "m", "o", "R", "s", "t", "T", "u", "U", "y"};
// OK:
string[] standardFormats = {"d", "D", "f", "F", "g", "G", "m", "o", "R", "s", "t", "T", "u", "U", "y"};
var now = DateTime.Now;
foreach (var format in standardFormats)
    Console.WriteLine("{0}: {1}", format, now.ToString(format));
Console.WriteLine("--------------------------------------------------------------------------------------------------");

var epoch = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
Console.WriteLine(epoch);

Console.WriteLine(DateTime.Now);
Console.WriteLine(DateTime.UtcNow);
Console.WriteLine(DateTime.UtcNow.ToLocalTime());

// Like std::time(NULL);
var totalSecondsSinceEpoch = (DateTime.UtcNow - epoch).TotalSeconds;
Console.WriteLine(totalSecondsSinceEpoch);

var dataTimeOffsetNow = DateTimeOffset.Now;
Console.WriteLine(dataTimeOffsetNow);
Console.WriteLine(dataTimeOffsetNow.ToUnixTimeSeconds());
Console.WriteLine(dataTimeOffsetNow.ToUnixTimeMilliseconds());

// References:
// https://stackoverflow.com/questions/7003373/how-to-get-datetime-now-in-yyyy-mm-ddthhmmsstzd-format-using-c-sharp
// [How do I get epoch time in C#?](https://stackoverflow.com/questions/9453101/how-do-i-get-epoch-time-in-c)
// [How do you convert epoch time in C#?](https://stackoverflow.com/questions/2883576/how-do-you-convert-epoch-time-in-c)
// [Get DateTime.Now with milliseconds precision](https://stackoverflow.com/questions/16032451/get-datetime-now-with-milliseconds-precision)
// [How can I convert a Unix timestamp to DateTime and vice versa?](https://stackoverflow.com/questions/249760/how-can-i-convert-a-unix-timestamp-to-datetime-and-vice-versa)
