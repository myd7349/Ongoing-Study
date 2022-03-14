C# 6.0 introduces [read-only auto-implemented property](https://stackoverflow.com/questions/2480503/is-read-only-auto-implemented-property-possible)

[C# atomic property with ONLY get, how to set the value?](https://stackoverflow.com/questions/52467520/c-sharp-atomic-property-with-only-get-how-to-set-the-value) 

Example: https://github.com/protocolbuffers/protobuf/blob/c60aaf79e63b911b2c04c04e1eacb4f3c36ef790/csharp/src/Google.Protobuf/Reflection/FieldDescriptor.cs#L54

```csharp
public class MyClass
{
    public MyClass()
    {
        Foo = 42; // OK
    }

    public int Foo
    {
        get;
    }
}
```

Before C# 6.0, we have to do similar things like this:

```csharp
public class MyClass
{
    public MyClass()
    {
        Foo = 42;
    }

    public int Foo
    {
        get;
        private set; // 
    }
}
```

Otherwise, the compiler will give this error:

> error CS0840: 'MyClass.Foo.get' must declare a body because it is not marked abstract or extern. Automatically implemented properties must define both get and set accessors.

[CA1819: Properties should not return arrays. Does this happen only with arrays? If yes, why?](https://softwareengineering.stackexchange.com/questions/210922/ca1819-properties-should-not-return-arrays-does-this-happen-only-with-arrays)

[CA1819: Properties should not return arrays](https://docs.microsoft.com/en-us/visualstudio/code-quality/ca1819?view=vs-2019)

[Override get, but not set](https://stackoverflow.com/questions/2026546/override-get-but-not-set)

[How do I create a delegate for a .NET property?](https://stackoverflow.com/questions/724143/how-do-i-create-a-delegate-for-a-net-property)

[Delegates as Properties: Bad Idea?](https://stackoverflow.com/questions/7575059/delegates-as-properties-bad-idea)

https://github.com/Fody/PropertyChanged

[Init only setters - C# 9.0 draft specifications | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/proposals/csharp-9.0/init)

- [command-line-api/Option{T}.cs at 941a651515db4a3889f9f43f124281a5fffb5f81 · dotnet/command-line-api · GitHub](https://github.com/dotnet/command-line-api/blob/941a651515db4a3889f9f43f124281a5fffb5f81/src/System.CommandLine/Option%7BT%7D.cs#L68)

[Raise an event whenever a property's value changed?](https://stackoverflow.com/questions/2246777/raise-an-event-whenever-a-propertys-value-changed)

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

[C# WPF UI Tutorials: 03 - View Model MVVM Basics](https://www.youtube.com/watch?v=U2ZvZwDZmJU)

- [Fody.PropertyChanged](https://github.com/Fody/PropertyChanged)
