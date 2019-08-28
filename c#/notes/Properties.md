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
