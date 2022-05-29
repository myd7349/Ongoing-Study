```csharp
public static IEnumerable<Record> ReadRecords(string filePath)
{
    if (!File.Exists(filePath))
        return Enumerable.Empty<Record>();

    using (var fileStream = File.OpenRead(filePath))
    {
        return ReadRecords(fileStream); // Not OK
    }
}

public static IEnumerable<Record> ReadRecords(Stream stream)
{
    if (stream == null)
        throw new ArgumentNullException(nameof(stream));

    Record record = null;

    do
    {
        record = Serializer.DeserializeWithLengthPrefix<Record>(stream, PrefixStyle.Fixed32);
        if (record != null)
            yield return record;

    } while (record != null);
}

```

```csharp
public static IEnumerable<Record> ReadRecords(string filePath)
{
    if (!File.Exists(filePath))
        yield from Enumerable.Empty<Record>();

    using (var fileStream = File.OpenRead(filePath))
    {
        yield from ReadRecords(fileStream);
    }
}

public static IEnumerable<Record> ReadRecords(Stream stream)
{
    if (stream == null)
        throw new ArgumentNullException(nameof(stream));

    Record record = null;

    do
    {
        record = Serializer.DeserializeWithLengthPrefix<Record>(stream, PrefixStyle.Fixed32);
        if (record != null)
            yield return record;

    } while (record != null);
}
```

[Yielding from multiple generators RRS feed](https://social.msdn.microsoft.com/Forums/vstudio/en-US/6b9918c2-6ede-4770-902c-065c9d977f5d/yielding-from-multiple-generators?forum=csharpgeneral)

> C# has no 'yield from' equivalent, so you would indeed have to do the iteration in the outer generator, in this case.

```csharp
public static IEnumerable<Record> ReadRecords(string filePath)
{
    if (File.Exists(filePath))
    {
        using (var fileStream = File.OpenRead(filePath))
        {
            foreach (var record in ReadRecords(fileStream))
                yield return record;
        }
    }
}

public static IEnumerable<Record> ReadRecords(Stream stream)
{
    if (stream == null)
        throw new ArgumentNullException(nameof(stream));

    Record record = null;

    do
    {
        record = Serializer.DeserializeWithLengthPrefix<Record>(stream, PrefixStyle.Fixed32);
        if (record != null)
            yield return record;

    } while (record != null);
}
```
