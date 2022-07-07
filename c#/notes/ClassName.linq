<Query Kind="Program" />

class A
{
    public virtual void Do()
    {
        Console.WriteLine(GetType().Name);
    }
}

class B : A
{
}

void Main()
{
    var b = new B();
    b.Do();
}


// References:
// [C# getting its own class name](https://stackoverflow.com/questions/2113069/c-sharp-getting-its-own-class-name)
