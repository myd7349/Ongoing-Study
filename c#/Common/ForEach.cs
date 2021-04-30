// 2017-07-13T10:32+08:00
// LINQ-style ForEach to consume an enumerable object.
using System;
using System.Collections.Generic;

namespace Common.Linq
{
    public static partial class EnumerableExtension
    {
        public static void ForEach<TSource>(this IEnumerable<TSource> source, Action<TSource> predicate)
        {
            source.ForEach((item, _) => predicate(item));
        }

        public static void ForEach<TSource>(this IEnumerable<TSource> source, Action<TSource, int> predicate)
        {
            if (source == null)
            {
                throw new ArgumentNullException("source");
            }

            if (predicate == null)
            {
                throw new ArgumentNullException("predicate");
            }

            int index = 0;

            foreach (var item in source)
                predicate(item, index++);
        }
    }
}

// References:
// [LINQ equivalent of foreach for IEnumerable<T>](https://stackoverflow.com/questions/200574/linq-equivalent-of-foreach-for-ienumerablet)
// [Linq Style "For Each"](https://stackoverflow.com/questions/1509442/linq-style-for-each)
// GitHub: dotnet/corefx/src/System.Linq/src/System/Linq/Where.cs
// [foreach with index](https://stackoverflow.com/questions/521687/foreach-with-index)
// https://github.com/morelinq/MoreLINQ#foreach
// C# 6.0 in a Nutshell, P301: Array.ForEach
