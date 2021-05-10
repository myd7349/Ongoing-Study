<Query Kind="Statements" />

Console.WriteLine($"{TimeSpan.FromMilliseconds(1)}");
Console.WriteLine($"{new TimeSpan(0, 0, 0, 0, 1)}");

// References:
// [Millisecond interval for DispatcherTimer](https://stackoverflow.com/questions/30581756/millisecond-interval-for-dispatchertimer)
// [DispatcherTimer with interval 0,0,1 is not exactly 1 second?](https://stackoverflow.com/questions/10991051/dispatchertimer-with-interval-0-0-1-is-not-exactly-1-second)
// [Difference between Synchronization Context and Dispatcher](https://stackoverflow.com/questions/24671883/difference-between-synchronization-context-and-dispatcher)
