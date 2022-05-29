[CA1838: Avoid `StringBuilder` parameters for P/Invokes](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1838)

> ```csharp
> [DllImport("MyLibrary", CharSet = CharSet.Unicode)]
> private static extern unsafe void Foo([Out] char[] buffer, ref int length);
> 
> public void Bar()
> {
>     int BufferSize = ...
>     char[] buffer = ArrayPool<char>.Shared.Rent(BufferSize);
>     try
>     {
>         int len = buffer.Length;
>         Foo(buffer, ref len);
>         string result = new string(buffer);
>     }
>     finally
>     {
>         ArrayPool<char>.Shared.Return(buffer);
>     }
> }
> ```

[Correct way of Renting and Returning a multi-dimensional array in C# from shared ArrayPool?](https://stackoverflow.com/questions/67231958/correct-way-of-renting-and-returning-a-multi-dimensional-array-in-c-sharp-from-s)

[Avoiding Array Pitfalls in C# .NET](https://blog.randes.me/avoiding-array-pitfalls-in-c-net/)

[Pooling large arrays with ArrayPool](https://adamsitnik.com/Array-Pool/)

[ArrayPool vs MemoryPool—minimizing allocations in AIS.NET](https://endjin.com/blog/2020/09/arraypool-vs-memorypool-minimizing-allocations-ais-dotnet)

[Difference between MemoryPool<T> and ArrayPool<T>](https://stackoverflow.com/questions/61856306/difference-between-memorypoolt-and-arraypoolt)

[Is ArrayPool<T>.Rent(Int32) Method thread-safe?](https://stackoverflow.com/questions/53273277/is-arraypoolt-rentint32-method-thread-safe)
