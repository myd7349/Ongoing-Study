2017-11-23T09:10+08:00

```csharp
var objs = new object[] { 42, 3.14, 8080, "Hello, world!", 21 };

// Print all integers in objs
foreach (var i in objs.Where(elem => elem is int).Cast<int>())
    Console.WriteLine(i);
    
// Use `OfType` instead of `Where`+`Cast`
foreach (var i in objs.OfType<int>())
    Console.WriteLine(i);
```
