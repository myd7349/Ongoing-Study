[How to initialize a List<T> to a given size (as opposed to capacity)?](https://stackoverflow.com/questions/466946/how-to-initialize-a-listt-to-a-given-size-as-opposed-to-capacity)

```csharp
List<string> L = new List<string> ( new string[10] );
```

[When should I use a List vs a LinkedList](https://stackoverflow.com/questions/169973/when-should-i-use-a-list-vs-a-linkedlist)

> In most cases, List<T> is more useful. LinkedList<T> will have less cost when adding/removing items in the middle of the list, whereas List<T> can only cheaply add/remove at the end of the list.
> 
> LinkedList<T> is only at it's most efficient if you are accessing sequential data (either forwards or backwards) - random access is relatively expensive since it must walk the chain each time (hence why it doesn't have an indexer). However, because a List<T> is essentially just an array (with a wrapper) random access is fine.
> 
> List<T> also offers a lot of support methods - Find, ToArray, etc; however, these are also available for LinkedList<T> with .NET 3.5/C# 3.0 via extension methods - so that is less of a factor.

[How to remove elements from a generic list while iterating over it?](https://stackoverflow.com/questions/1582285/how-to-remove-elements-from-a-generic-list-while-iterating-over-it)
  
[Removing from a LinkedList](https://stackoverflow.com/questions/8195242/removing-from-a-linkedlist)
