using System;
using System.Collections.Generic;

namespace Common.Linq
{
    public static partial class EnumerableExtension
    {
        public static IEnumerable<TResult> Zip<T1, T2, T3, TResult>(this IEnumerable<T1> source, IEnumerable<T2> second, IEnumerable<T3> third, Func<T1, T2, T3, TResult> func)
        {
            using (var e1 = source.GetEnumerator())
            using (var e2 = second.GetEnumerator())
            using (var e3 = third.GetEnumerator())
            {
                while (e1.MoveNext() && e2.MoveNext() && e3.MoveNext())
                    yield return func(e1.Current, e2.Current, e3.Current);
            }
        }

        public static IEnumerable<TResult> Zip<T1, T2, T3, T4, TResult>(this IEnumerable<T1> source, IEnumerable<T2> second, IEnumerable<T3> third, IEnumerable<T4> fourth, Func<T1, T2, T3, T4, TResult> func)
        {
            using (var e1 = source.GetEnumerator())
            using (var e2 = second.GetEnumerator())
            using (var e3 = third.GetEnumerator())
            using (var e4 = fourth.GetEnumerator())
            {
                while (e1.MoveNext() && e2.MoveNext() && e3.MoveNext() && e4.MoveNext())
                    yield return func(e1.Current, e2.Current, e3.Current, e4.Current);
            }
        }

        public static IEnumerable<TResult> Zip<T1, T2, T3, T4, T5, TResult>(this IEnumerable<T1> source, IEnumerable<T2> second, IEnumerable<T3> third, IEnumerable<T4> fourth, IEnumerable<T5> fifth, Func<T1, T2, T3, T4, T5, TResult> func)
        {
            using (var e1 = source.GetEnumerator())
            using (var e2 = second.GetEnumerator())
            using (var e3 = third.GetEnumerator())
            using (var e4 = fourth.GetEnumerator())
            using (var e5 = fifth.GetEnumerator())
            {
                while (e1.MoveNext() && e2.MoveNext() && e3.MoveNext() && e4.MoveNext() && e5.MoveNext())
                    yield return func(e1.Current, e2.Current, e3.Current, e4.Current, e5.Current);
            }
        }
    }
}

// References:
// [Enumerable.Zip](https://learn.microsoft.com/en-us/dotnet/api/system.linq.enumerable.zip?view=net-6.0)
// [How to combine more than two generic lists in C# Zip?](https://stackoverflow.com/questions/10297124/how-to-combine-more-than-two-generic-lists-in-c-sharp-zip)
// https://github.com/morelinq/MoreLINQ#zipshortest
// https://github.com/morelinq/MoreLINQ#ziplongest

