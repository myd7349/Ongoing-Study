<Query Kind="Program" />

void Swap<T>(ref T lhs, ref T rhs)
{
    T t = lhs;
    lhs = rhs;
    rhs = t;
}


void Main()
{
    int x = 3;
    int y = 4;
    Console.WriteLine($"x = {x}, y = {y}");
    Swap(ref x, ref y);
    Console.WriteLine($"x = {x}, y = {y}");

    var array = new int[] { 3, 4 };
    Console.WriteLine($"[0] = {array[0]}, [1] = {array[1]}");
    Swap(ref array[0], ref array[1]);
    Console.WriteLine($"[0] = {array[0]}, [1] = {array[1]}");

    var list = new List<int> { 3, 4 };
    Console.WriteLine($"[0] = {list[0]}, [1] = {list[1]}");
    // CS0206 A property or indexer may not be passed as an out or ref parameter.
    //Swap(ref list[0], ref list[1]);
    //Console.WriteLine($"[0] = {list[0]}, [1] = {list[1]}");
}

// References:
// [Is there a generic swap method in the framework?](https://stackoverflow.com/questions/922505/is-there-a-generic-swap-method-in-the-framework)