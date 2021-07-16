[C# “internal” access modifier when doing unit testing](https://stackoverflow.com/questions/358196/c-sharp-internal-access-modifier-when-doing-unit-testing)

> ```csharp
> // Properties\AssemblyInfo.cs
> using System.Runtime.CompilerServices;
> 
> [assembly:InternalsVisibleTo("MyTests")]
> ```

[Making code internal but available for unit testing from other projects](https://stackoverflow.com/questions/106907/making-code-internal-but-available-for-unit-testing-from-other-projects)

[How to: Implement Property Change Notification](https://docs.microsoft.com/en-us/dotnet/desktop/wpf/data/how-to-implement-property-change-notification?view=netframeworkdesktop-4.8)

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

