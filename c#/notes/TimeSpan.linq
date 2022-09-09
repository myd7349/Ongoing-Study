<Query Kind="Statements" />

Console.WriteLine($"{TimeSpan.FromMilliseconds(1)}");
Console.WriteLine($"{new TimeSpan(0, 0, 0, 0, 1)}");

Console.WriteLine(DateTime.Now.ToString("HH:mm:ss.fff"));

var timePoint = TimeSpan.Zero;
try
{
    Console.WriteLine(timePoint.ToString("HH:mm:ss.fff"));
}
catch (FormatException e)
{
    Console.WriteLine(e);
}

Console.WriteLine(timePoint.ToString("h'h 'm'm 's's'"));

timePoint = TimeSpan.FromMilliseconds(3600 * 1000 + 60 * 1000 + 1000 + 200);
Console.WriteLine(timePoint.ToString("hh':'mm':'ss'.'fff"));
Console.WriteLine(timePoint.ToString("hh\\:mm\\:ss\\.fff"));

timePoint = TimeSpan.FromMilliseconds(24 * 3600 * 1000 - 1);
Console.WriteLine(timePoint.ToString("hh\\:mm\\:ss\\.fff"));

timePoint = TimeSpan.FromMilliseconds(24 * 3600 * 1000);
Console.WriteLine(timePoint.ToString("hh\\:mm\\:ss\\.fff"));
Console.WriteLine(timePoint.ToString(@"hh\:mm\:ss\.fff"));

timePoint = TimeSpan.FromHours(25);
Console.WriteLine(timePoint.ToString(@"hh\:mm\:ss\.fff"));

// References:
// [Millisecond interval for DispatcherTimer](https://stackoverflow.com/questions/30581756/millisecond-interval-for-dispatchertimer)
// [DispatcherTimer with interval 0,0,1 is not exactly 1 second?](https://stackoverflow.com/questions/10991051/dispatchertimer-with-interval-0-0-1-is-not-exactly-1-second)
// [Difference between Synchronization Context and Dispatcher](https://stackoverflow.com/questions/24671883/difference-between-synchronization-context-and-dispatcher)
// [TimeSpan ToString format](https://stackoverflow.com/questions/11077711/timespan-tostring-format)
// > (Note that even spaces need to be quoted - that's what was wrong with my first attempt.)
// > EDIT: As noted, this won't work beyond 24 hours. Also note that alternatives are available via Noda Time too :)
// [Display duration in milliseconds](https://stackoverflow.com/questions/9565740/display-duration-in-milliseconds)
// [Use String.Format on a TimeSpan to output full seconds without milliseconds](https://stackoverflow.com/questions/3545508/use-string-format-on-a-timespan-to-output-full-seconds-without-milliseconds)
// [How to format TimeSpan in XAML](https://stackoverflow.com/questions/4563081/how-to-format-timespan-in-xaml)
// [Format TimeSpan greater than 24 hour](https://stackoverflow.com/questions/3505230/format-timespan-greater-than-24-hour)
// [C# convert int to string with padding zeros?](https://stackoverflow.com/questions/4325267/c-sharp-convert-int-to-string-with-padding-zeros)
