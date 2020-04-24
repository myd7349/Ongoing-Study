<Query Kind="Program" />

IEnumerable<int> Foo()
{
    int i = 0;
    while (true)
    {
        if (i < 5)
        {
            yield return i;
        }
        else
        {
            // note that i++ will not be executed after this
            yield break;
        }
        i++;
    }
	
	Console.Out.WriteLine("Won't see me");
}

void Main()
{
    foreach (var i in Foo())
        Console.Out.WriteLine(i);
}

// References:
// https://stackoverflow.com/questions/231893/what-does-yield-break-do-in-c