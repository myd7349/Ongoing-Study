enum TypeA
{
    A,
    B
}

enum TypeB
{
    A = 42,
    B
}

class MyClass
{
    public TypeA A { get; set; }

    public TypeB B { get; set; }
}

Console.WriteLine(new MyClass().A);
Console.WriteLine(new MyClass().B);

// Output:
// A
// 0
