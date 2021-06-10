<Query Kind="Program" />

void Foo()
{
    Console.WriteLine($"{MethodBase.GetCurrentMethod()}");
}

void Main()
{
    Console.WriteLine($"{MethodBase.GetCurrentMethod()}");

    Foo();
}

// References:
// [Why do loggers recommend using a logger per class?](https://stackoverflow.com/questions/3143929/why-do-loggers-recommend-using-a-logger-per-class)
