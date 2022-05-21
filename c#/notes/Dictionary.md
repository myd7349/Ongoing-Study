https://github.com/aspnet/Configuration/blob/f64994e0655659faefccead7ccb5c1edbfd4d4ba/src/Config.Ini/IniConfigurationProvider.cs#L36

> ```csharp
> var data = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
> ```

Dictionary

System.Collections.Specialized.OrderedDictionary

System.Collections.Generic.SortedDictionary

System.Collections.Generic.SortedList

[How do I convert from a Dictionary to a SortedDictionary using LINQ in C#?](https://stackoverflow.com/questions/451717/how-do-i-convert-from-a-dictionary-to-a-sorteddictionary-using-linq-in-c)

[Why is Dictionary preferred over Hashtable in C#?](https://stackoverflow.com/questions/301371/why-is-dictionary-preferred-over-hashtable-in-c)

> ```csharp
> class DependencyProperty
> {
>     private static Hashtable PropertyFromName = new Hashtable();
> }
> ```
>
> 

https://github.com/ScottPlot/ScottPlot/blob/4.1.45/src/ScottPlot4/ScottPlot.WPF/WpfPlot.xaml.cs#L109-L118

```csharp
Cursors = new Dictionary<Cursor, System.Windows.Input.Cursor>()
{
    [ScottPlot.Cursor.Arrow] = System.Windows.Input.Cursors.Arrow,
    [ScottPlot.Cursor.WE] = System.Windows.Input.Cursors.SizeWE,
    [ScottPlot.Cursor.NS] = System.Windows.Input.Cursors.SizeNS,
    [ScottPlot.Cursor.All] = System.Windows.Input.Cursors.SizeAll,
    [ScottPlot.Cursor.Crosshair] = System.Windows.Input.Cursors.Cross,
    [ScottPlot.Cursor.Hand] = System.Windows.Input.Cursors.Hand,
    [ScottPlot.Cursor.Question] = System.Windows.Input.Cursors.Help,
};
```

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

[Hashtable with MultiDimensional Key in C#](https://stackoverflow.com/questions/689940/hashtable-with-multidimensional-key-in-c-sharp)

[Multi-key dictionary in c#?](https://stackoverflow.com/questions/1171812/multi-key-dictionary-in-c)
