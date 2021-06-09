<Query Kind="Program" />

void Main()
{
    Console.WriteLine($"Up Time: {GetUpTime()}");
}

TimeSpan GetUpTime()
{
    using (var upTime = new PerformanceCounter("System", "System Up Time"))
    {
        upTime.NextValue(); // Call this an extra time before reading its value
        return TimeSpan.FromSeconds(upTime.NextValue());
    }
}

// References:
// [Retrieve system uptime using C#](https://stackoverflow.com/questions/972105/retrieve-system-uptime-using-c-sharp)
