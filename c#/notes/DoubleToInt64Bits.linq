<Query Kind="Statements" />

var pi = Math.PI;

unsafe
{
    var num = *(long *)&pi;
	Console.WriteLine("{0:X8}", num);
}


Console.WriteLine("{0:X8}", BitConverter.DoubleToInt64Bits(pi));
Console.WriteLine("{0:X8}", (long)pi);

// References:
// Ongoing-Study/c#/Common/BinaryWriterEx.cs
