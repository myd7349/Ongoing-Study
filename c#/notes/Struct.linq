<Query Kind="Program" />

struct Point
{
    public Point(int x = 1, int y = 1)
    {
        this.x = x;
        this.y = y;
    }

    public int x;
    public int y;

    public override string ToString()
    {
        return string.Format("Point({0}, {1})", x, y);
    }
}

void Main()
{
    Console.WriteLine(new Point());
    Console.WriteLine(new Point(3));
    Console.WriteLine(new Point(3, 4));
}


// References:
// [How to make a default value for the struct in C#?](https://stackoverflow.com/questions/39846708/how-to-make-a-default-value-for-the-struct-in-c)
