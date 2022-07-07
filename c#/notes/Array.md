[Is Array.Copy safe when the source and destination are the same array?](https://stackoverflow.com/questions/11149668/is-array-copy-safe-when-the-source-and-destination-are-the-same-array)

[How to sum up an array of integers in C#](https://stackoverflow.com/questions/2419343/how-to-sum-up-an-array-of-integers-in-c-sharp)

C# 6.0 in a Nutshell, P301

> Array.Clear doesn't affect the size of the array. This is in contrast to the usual use of Clear (such as in ICollection<T>.clear), where the collection is reduced to zero elements.

[ArraySegment](https://github.com/joaoportela/CircularBuffer-CSharp/blob/444a9ef47f03f5e687b9ba4a8be0de86a5a83027/CircularBuffer/CircularBuffer.cs#L259-L287)

[Convert 2 dimensional array](https://stackoverflow.com/questions/641499/convert-2-dimensional-array)

[Fast way to convert a two dimensional array to a List ( one dimensional )](https://stackoverflow.com/questions/5132397/fast-way-to-convert-a-two-dimensional-array-to-a-list-one-dimensional)

[What's the best way to extract a one-dimensional array from a rectangular array in C#?](https://stackoverflow.com/questions/232545/whats-the-best-way-to-extract-a-one-dimensional-array-from-a-rectangular-array)

[Getting a double[] row array of a double[,] rectangular array](https://stackoverflow.com/questions/2977242/getting-a-double-row-array-of-a-double-rectangular-array)

```csharp
var array1 = new double[3,4] { { 0, 0, 0, 0 }, { 1, 1, 1, 1 }, { 2, 2, 2, 2 } };
Console.WriteLine(array1);
try
{
    Console.WriteLine((double[])(object)array1);
}
catch (Exception ex)
{
    Console.WriteLine(ex);
}
var array2 = new double[Buffer.ByteLength(array1) / sizeof(double)];
Buffer.BlockCopy(array1, 0, array2, 0, Buffer.ByteLength(array1));
Console.WriteLine(array2);
```

Array.Empty<T>():

```csharp
var array = Array.Empty<double>();
Console.WriteLine(array);
Console.WriteLine(array.GetType());
Console.WriteLine(array.Length);

// References:
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.IO.Ports/src/System/IO/Ports/SerialPort.Win32.cs
```

[Avoiding Array Pitfalls in C# .NET](https://levelup.gitconnected.com/avoiding-array-pitfalls-in-c-net-a229a29bc45d)

> Bottom-Line: Avoid allocating new empty arrays. Use Array.Empty<T>() instead.

[How to sort a list of objects by a specific field in C#?](https://stackoverflow.com/questions/1301822/how-to-sort-a-list-of-objects-by-a-specific-field-in-c)

[How to sort an array containing class objects by a property value of a class instance?](https://stackoverflow.com/questions/1304278/how-to-sort-an-array-containing-class-objects-by-a-property-value-of-a-class-ins)
