[ArrayList Class](https://docs.microsoft.com/en-us/dotnet/api/system.collections.arraylist?view=net-5.0)

> We don't recommend that you use the `ArrayList` class for new development. Instead, we recommend that you use the generic [List](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-5.0) class. The [ArrayList](https://docs.microsoft.com/en-us/dotnet/api/system.collections.arraylist?view=net-5.0) class is designed to hold heterogeneous collections of objects.  However, it does not always offer the best performance. Instead, we  recommend the following:
>
> - For a heterogeneous collection of objects, use the `List<Object>` (in C#) or `List(Of Object)` (in Visual Basic) type.
> - For a homogeneous collection of objects, use the [List](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-5.0) class.
>    See [Performance Considerations](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-5.0#performance-considerations) in the [List](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.list-1?view=net-5.0) reference topic for a discussion of the relative performance of these classes.  See [Non-generic collections shouldn't be used](https://github.com/dotnet/platform-compat/blob/master/docs/DE0006.md) on GitHub for general information on the use of generic instead of non-generic collection types.

C# 6.0 in a Nutshell, P306:

> Internally, List<T> and ArrayList work by maintaining an internal array of objects, replaced with a larger array upon reaching capacity. Appending elements is efficient(since there is usually a free slot at the end), but inserting elements can be slow(since all elements after the insertion point have to be shifted to make a free slot).

[When should I use a List vs a LinkedList](https://stackoverflow.com/questions/169973/when-should-i-use-a-list-vs-a-linkedlist)

