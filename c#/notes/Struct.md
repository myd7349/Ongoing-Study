[How to initialize struct?](https://stackoverflow.com/questions/4420094/how-to-initialize-struct)

[Field Initializer in Struct C#](https://social.msdn.microsoft.com/Forums/vstudio/en-US/020aec58-1903-4379-a768-052c9d45783d/field-initializer-in-struct-c)

[Copying byte array to various fields in class/struct in C#](https://stackoverflow.com/questions/7030150/copying-byte-array-to-various-fields-in-class-struct-in-c-sharp)
```csharp
unsafe struct ExampleClass
{
   public ulong field1;
   public uint field2
   public ushort field3
   public fixed byte field4[18];

   public static ExampleClass ReadStruct(byte[] data)
   {
       fixed (byte* pb = &data[0])
       {
           return *(ExampleClass*)pb;
       }
   }
}
```

[Cannot take the address of, get the size of, or declare a pointer to a managed type](https://stackoverflow.com/questions/13299153/cannot-take-the-address-of-get-the-size-of-or-declare-a-pointer-to-a-managed-t)

[What's the best way to write a short[] array to a file in C#?](https://stackoverflow.com/questions/224239/whats-the-best-way-to-write-a-short-array-to-a-file-in-c)

```csharp
[MarshalAs(UnmanagedType.ByValArray, SizeConst = 10, ArraySubType = UnmanagedType.U2)]
public ushort[] Data;
```

