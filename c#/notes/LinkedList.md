C# 6.0 in a Nutshell, P306:

> Internally, List<T> and ArrayList work by maintaining an internal array of objects, replaced with a larger array upon reaching capacity. Appending elements is efficient(since there is usually a free slot at the end), but inserting elements can be slow(since all elements after the insertion point have to be shifted to make a free slot).

[When should I use a List vs a LinkedList](https://stackoverflow.com/questions/169973/when-should-i-use-a-list-vs-a-linkedlist)

