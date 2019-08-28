<Query Kind="Statements" />

Console.WriteLine(DateTime.Now.ToString("yyyy-MM-ddTHH:mm:sszzz"));

var epoch = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
Console.WriteLine(epoch);

Console.WriteLine(DateTime.Now);
Console.WriteLine(DateTime.UtcNow);
Console.WriteLine(DateTime.UtcNow.ToLocalTime());

// Like std::time(NULL);
var totalSecondsSinceEpoch = (DateTime.UtcNow - epoch).TotalSeconds;
Console.WriteLine(totalSecondsSinceEpoch);

// References:
// https://stackoverflow.com/questions/7003373/how-to-get-datetime-now-in-yyyy-mm-ddthhmmsstzd-format-using-c-sharp
// [How do I get epoch time in C#?](https://stackoverflow.com/questions/9453101/how-do-i-get-epoch-time-in-c)
// [How do you convert epoch time in C#?](https://stackoverflow.com/questions/2883576/how-do-you-convert-epoch-time-in-c)
