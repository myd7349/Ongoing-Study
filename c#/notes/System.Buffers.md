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

