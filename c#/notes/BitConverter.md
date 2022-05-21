```csharp
byte b1 = 0xFF;
byte b2 = 0x12;
byte b3 = 0x34;

int i24 = ((b1 << 24) | (b2 << 16) | (b3 << 8)) >> 8;
Console.WriteLine($"{i24:X}: {i24}");

var buffer = new byte[] { 0, b3, b2, b1 };
i24 = BitConverter.ToInt32(buffer, 0) / 256;
Console.WriteLine($"{i24:X}: {i24}");

// References:
// [How do you convert 3 bytes into a 24 bit number in C#?](https://stackoverflow.com/questions/3345553/how-do-you-convert-3-bytes-into-a-24-bit-number-in-c)
// [Converting 24 bit integer (2s complement) to 32 bit integer in C++](https://stackoverflow.com/questions/35876000/converting-24-bit-integer-2s-complement-to-32-bit-integer-in-c)

```
