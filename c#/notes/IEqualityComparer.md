IEqualityComparer

[PEP 455 – Adding a key-transforming dictionary to collections](https://peps.python.org/pep-0455/)

[Linq IEqualityComparer<string> Ignore Case](https://stackoverflow.com/questions/61175952/linq-iequalitycomparerstring-ignore-case)

[Efficiency of using IEqualityComparer in Dictionary vs HashCode and Equals()](https://stackoverflow.com/questions/7143948/efficiency-of-using-iequalitycomparer-in-dictionary-vs-hashcode-and-equals)

```csharp
public class StringIEqualityComparer : IEqualityComparer<string>
{
    public bool Equals(string x, string y)
    {
        return x.Equals(y, StringComparison.OrdinalIgnoreCase);
    }

    public int GetHashCode(string obj)
    {
        return obj.GetHashCode();
    }
}

static void Main()
{
    var dict = new Dictionary<string, int>(new StringIEqualityComparer());
    dict["Five"] = 5;
    Console.WriteLine(dict["Five"]);
    Console.WriteLine(dict.ContainsKey("Five"));
    Console.WriteLine(dict.ContainsKey("five"));

    dict = new Dictionary<string, int>(StringComparer.OrdinalIgnoreCase);
    dict["Five"] = 5;
    Console.WriteLine(dict["Five"]);
    Console.WriteLine(dict.ContainsKey("Five"));
    Console.WriteLine(dict.ContainsKey("five"));
}

/*
Output:
5
True
False
5
True
True
*/
```
