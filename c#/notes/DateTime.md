[Choose between DateTime, DateOnly, DateTimeOffset, TimeSpan, TimeOnly, and TimeZoneInfo](https://learn.microsoft.com/en-us/dotnet/standard/datetime/choosing-between-datetime)

[How to subtract a year from the datetime?](https://stackoverflow.com/questions/2992451/how-to-subtract-a-year-from-the-datetime)

[Difference between System.DateTime.Now and System.DateTime.Today](https://stackoverflow.com/questions/6545254/difference-between-system-datetime-now-and-system-datetime-today)

[Parse date and time strings in .NET](https://docs.microsoft.com/en-us/dotnet/standard/base-types/parsing-datetime)

[Converting a String to DateTime](https://stackoverflow.com/questions/919244/converting-a-string-to-datetime)

```csharp
DateTime result;
if (DateTime.TryParseExact(
    "20220402-152310111",
    "yyyyMMdd-HHmmssfff",
    null,
    DateTimeStyles.AssumeLocal,
    out result))
    return result;
```

[How do I represent a time only value in .NET?](https://stackoverflow.com/questions/2037283/how-do-i-represent-a-time-only-value-in-net)
