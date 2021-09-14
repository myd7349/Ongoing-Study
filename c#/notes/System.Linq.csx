static IEnumerable<Tuple<T, T>> PairWiseV1<T>(this IEnumerable<T> enumerable)
{
    return enumerable
        .Zip(
            enumerable.Skip(1),
            (a, b) => Tuple.Create(a, b));
}


static IEnumerable<Tuple<T, T>> PairWiseV2<T>(this IEnumerable<T> enumerable)
{
    return enumerable
        .Where((x, i) => i % 2 == 0)
        .Zip(
            enumerable.Where((x, i) => i % 2 != 0),
            (a, b) => Tuple.Create(a, b));
}


var array = new []{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
foreach(var pair in array.PairWiseV1())
    Console.WriteLine(pair);

foreach(var pair in array.PairWiseV2())
    Console.WriteLine(pair);


// References:
// [Pair-wise iteration in C# or sliding window enumerator](https://stackoverflow.com/questions/577590/pair-wise-iteration-in-c-sharp-or-sliding-window-enumerator)
// https://github.com/morelinq/MoreLINQ/blob/master/MoreLinq/Pairwise.cs
// [How can I get every nth item from a List<T>?](https://stackoverflow.com/questions/682615/how-can-i-get-every-nth-item-from-a-listt)
