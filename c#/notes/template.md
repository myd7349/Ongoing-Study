[Generics syntax for multiple type parameter constraints](https://stackoverflow.com/questions/965580/c-sharp-generics-syntax-for-multiple-type-parameter-constraints)
```csharp
struct DataPack<T> where T : struct
{
    T X, Y, Z;
}

class DataUnpacker<T, TDataPack>
    where T : struct
    where TDataPack : struct
{
    public T[] Unpack(TDataPack)
    {
        ...
    }
}
```

[Template specialization](https://stackoverflow.com/questions/600978/how-to-do-template-specialization-in-c-sharp)
