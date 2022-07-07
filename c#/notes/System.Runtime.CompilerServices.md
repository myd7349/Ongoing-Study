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

[Inline functions in C#?](https://stackoverflow.com/questions/473782/inline-functions-in-c)

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

ILSpy+System.Core.dll:

> ```csharp
> [assembly: DefaultDllImportSearchPaths()]
> [assembly: TypeForwardedTo(typeof(Action))]
> ```

[Raise an event whenever a property's value changed?](https://stackoverflow.com/questions/2246777/raise-an-event-whenever-a-propertys-value-changed)

[MVVM for Beginners: Model-View-ViewModel Architecture for Xamarin.Forms, .NET MAUI, WPF, UWP, & More](https://youtu.be/Pso1MeX_HvI)

```csharp
protected void OnPropertyChanged(
    [System.Runtime.CompilerServices.CallerMemberName] string propertyName = "")
{
    OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
}

public string ImageFullPath
{
    get { return imageFullPath; }
    set
    {
        if (value != imageFullPath)
        {
            imageFullPath = value;
            OnPropertyChanged();
        }
    }
}
```

[Use of Attributes... INotifyPropertyChanged](https://stackoverflow.com/questions/1662745/use-of-attributes-inotifypropertychanged)

[ConditionalWeakTable<TKey,TValue>](https://learn.microsoft.com/en-us/dotnet/api/system.runtime.compilerservices.conditionalweaktable-2?view=net-6.0)

- [Understanding ConditionalWeakTable](https://stackoverflow.com/questions/18465630/understanding-conditionalweaktable)

- https://github.com/CommunityToolkit/dotnet/blob/main/CommunityToolkit.Diagnostics/Extensions/TypeExtensions.cs

- https://github.com/ronnieoverby/Overby.Extensions.Attachments

Unsafe.Add

- https://github.com/CommunityToolkit/dotnet/blob/main/CommunityToolkit.Diagnostics/Extensions/ValueTypeExtensions.cs

ConditionalWeakTable

- https://github.com/anakic/Jot/blob/master/Jot/Configuration/Trigger.cs
