- [Generator.Equals](https://github.com/diegofrata/Generator.Equals)

  - DeepL for Windows

[What's the difference between IEquatable and just overriding Object.Equals()?](https://stackoverflow.com/questions/2734914/whats-the-difference-between-iequatable-and-just-overriding-object-equals)

[IEquatable<T> Interface](https://learn.microsoft.com/en-us/dotnet/api/system.iequatable-1?view=net-6.0)

[Is there a complete IEquatable implementation reference?](https://stackoverflow.com/questions/1307493/is-there-a-complete-iequatable-implementation-reference)

```csharp
public class TypeModel : IEquatable<TypeModel>
{
    public TypeModel(string assemblyName, string typeName)
    {
    }

    public TypeModel(Type type)
    {
    }

    public string AssemblyName { get; set; }

    public string TypeName { get; set; }

    public string FullName => $"{AssemblyName}{Seperator}{TypeName}";

    public override string ToString()
    {
        return FullName;
    }

    //public override int GetHashCode()
    //{
    //    return FullName.GetHashCode();
    //}

    public bool Equals(TypeModel other)
    {
        if (ReferenceEquals(this, other))
            return true;

        if (ReferenceEquals(null, other))
            return false;

        return AssemblyName == other.AssemblyName && TypeName == other.TypeName;
    }

    //public override bool Equals(object other)
    //{
    //    return Equals(other as TypeModel);
    //}

    //public static bool operator ==(TypeModel lhs, TypeModel rhs)
    //{
    //    if (ReferenceEquals(lhs, null))
    //        return ReferenceEquals(rhs, null);

    //    return lhs.Equals(rhs);
    //}

    //public static bool operator !=(TypeModel lhs, TypeModel rhs)
    //{
    //    return !(lhs == rhs);
    //}

    internal const char Seperator = ':';
}
```

