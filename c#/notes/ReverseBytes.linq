<Query Kind="Statements" />

Console.WriteLine(BitConverter.IsLittleEndian);

UInt32 num = 0x2010;

Console.WriteLine(BitConverter.GetBytes(num));

var numView = BitConverter.GetBytes(num);
Array.Reverse(numView);

Console.WriteLine(numView);

Console.WriteLine("{0:x8}", num);
Console.WriteLine("{0:x8}", BitConverter.ToUInt32(numView, 0));

// References:
// https://social.msdn.microsoft.com/Forums/vstudio/en-US/c878e72e-d42e-417d-b4f6-1935ad96d8ae/converting-small-endian-to-big-endian-using-clong-value
// https://stackoverflow.com/questions/5784365/how-to-reverse-the-order-of-a-byte-array-in-c
// https://stackoverflow.com/questions/1358747/fast-little-endian-to-big-endian-conversion-in-asm
