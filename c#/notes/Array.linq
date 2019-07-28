<Query Kind="Program" />

void Main()
{
    var data = new int[] { 0, 1, 2, 3, 4 };
    for (int i = 5; i <= 10; ++i)
    {
        Console.WriteLine(data);
        Array.Copy(data, 1, data, 0, data.Length - 1);
        data[data.Length - 1] = i;
    }
}

// References:
// https://stackoverflow.com/questions/11149668/is-array-copy-safe-when-the-source-and-destination-are-the-same-array
