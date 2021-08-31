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
