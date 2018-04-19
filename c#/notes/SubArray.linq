<Query Kind="Statements" />

// 2018-03-26T15:13+08:00

// 1.
Console.WriteLine("----------");

var array = new int[] { 1, 1, 2, 3, 5, 8, 13 };
var subArray = new ArraySegment<int>(array, 2, 3);
foreach (var i in subArray)
    Console.WriteLine(i);
    

// 2.
Console.WriteLine("----------");

foreach (var i in array.Skip(2).Take(3))
    Console.WriteLine(i);
    
// 3.
Console.WriteLine("----------");

var subArray2 = new int[3];
Array.Copy(array, 2, subArray2, 0, 3);

foreach (var i in subArray2)
    Console.WriteLine(i);

// 4.
Console.WriteLine("----------");

unsafe void PrintSubArray(int[] arr, int start, int length)
{
    fixed (int *ptr = array)
    {
        int *pStart = ptr + start;
        for (int i = 0; i < length; ++i)
            Console.WriteLine(pStart[i]);
    }
}

PrintSubArray(array, 2, 3);

// References:
// https://github.com/dotnet/roslyn/issues/120
// https://www.codeproject.com/articles/1077634/csharp-feature-proposal-slicing
// https://stackoverflow.com/questions/406485/array-slices-in-c-sharp
// https://stackoverflow.com/questions/943635/getting-a-sub-array-from-an-existing-array
