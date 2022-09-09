[What is the difference between Span<T> and Memory<T> in C# 7.2?](https://stackoverflow.com/questions/47321691/what-is-the-difference-between-spant-and-memoryt-in-c-sharp-7-2)

[C# Checking if object is Span<T>](https://stackoverflow.com/questions/65202795/c-sharp-checking-if-object-is-spant)

[老王Plus的全栈](https://www.cnblogs.com/tiger-wang/p/14029853.html)

```csharp
Span<int> a = null;

Console.WriteLine(a.Length); // 0

foreach (var i in a)
    Console.WriteLine(i);

Console.WriteLine(a == null); // true
```
