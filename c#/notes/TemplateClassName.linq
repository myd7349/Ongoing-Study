<Query Kind="Program" />

class A<T>
{
    public string ToString() => nameof(T);
}

class B<T>
{
    public string ToString() => typeof(T).Name;
}

void Main()
{
    Console.WriteLine(new A<int>());
    Console.WriteLine(new B<int>());
    Console.WriteLine(new A<int>().ToString());
    Console.WriteLine(new B<int>().ToString());
}


// References:
// [how to I get the class name when I am passing in a generic in my method?](https://stackoverflow.com/questions/2534860/how-to-i-get-the-class-name-when-i-am-passing-in-a-generic-in-my-method)

