[C# “internal” access modifier when doing unit testing](https://stackoverflow.com/questions/358196/c-sharp-internal-access-modifier-when-doing-unit-testing)

> ```csharp
> // Properties\AssemblyInfo.cs
> using System.Runtime.CompilerServices;
> 
> [assembly:InternalsVisibleTo("MyTests")]
> ```

[Making code internal but available for unit testing from other projects](https://stackoverflow.com/questions/106907/making-code-internal-but-available-for-unit-testing-from-other-projects)

[How to: Implement Property Change Notification](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-implement-property-change-notification?view=netframeworkdesktop-4.8)

[Can you use reflection to find the name of the currently executing method?](https://stackoverflow.com/questions/44153/can-you-use-reflection-to-find-the-name-of-the-currently-executing-method)

```csharp
void Foo([CallerMemberName] string caller = null)
{
    Console.WriteLine("Caller: {0}", caller);
}

void Main()
{
    Foo();
}
```

https://github.com/EasyNetQ/EasyNetQ/blob/develop/Source/EasyNetQ/Internals/ReadOnlyMemoryStream.cs

> ```csharp
> [MethodImpl(MethodImplOptions.AggressiveInlining)]
> private static void ValidateReadArrayArguments(byte[] buffer, int offset, int count)
> {
>     if (buffer == null)
>         throw new ArgumentNullException(nameof(buffer));
> 
>     if (offset < 0)
>         throw new ArgumentOutOfRangeException(nameof(offset));
> 
>     if (count < 0 || buffer.Length - offset < count)
>         throw new ArgumentOutOfRangeException(nameof(count));
> }
> ```

