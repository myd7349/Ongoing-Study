<Query Kind="Program">
  <Namespace>System.ComponentModel</Namespace>
  <Namespace>System.Runtime.CompilerServices</Namespace>
</Query>

void Foo()
{
    Console.WriteLine($"{MethodBase.GetCurrentMethod()}");
}

void Bar([CallerMemberName] string name = null)
{
    Console.WriteLine($"{name}");
}

void Main()
{
    Console.WriteLine($"{MethodBase.GetCurrentMethod()}");

    Foo();

    Bar();
}

// References:
// [Why do loggers recommend using a logger per class?](https://stackoverflow.com/questions/3143929/why-do-loggers-recommend-using-a-logger-per-class)
// [How to: Implement Property Change Notification](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-implement-property-change-notification?view=netframeworkdesktop-4.8)
