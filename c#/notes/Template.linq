<Query Kind="Program" />

void Foo<T>(T x)
{
    Console.WriteLine("Foo<T>(T)");
}

void Foo(double x)
{
    Console.WriteLine("Foo(double)");
}

void Foo(short x)
{
    Console.WriteLine("Foo(short)");
}

void Bar<T>(T x)
{
    Foo(x);
}

void Main()
{
    Bar(3.14);
    Bar((short)12);
}

// References:
// https://stackoverflow.com/questions/600978/how-to-do-template-specialization-in-c-sharp
