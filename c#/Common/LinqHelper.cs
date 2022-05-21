namespace Common
{
    using System;
    using System.Collections.Generic;
    using System.Linq;

    public static class LinqHelper
    {
        public static bool IsUnique<T>(this IEnumerable<T> x)
        {
            if (x == null)
                throw new ArgumentNullException("x");

            return x.Distinct().Count() == x.Count();
        }

        public static bool Contains(this IEnumerable<string> list, StringComparison comparison)
        {
            return false;
        }

        public static bool IsOrdered<T>(this IEnumerable<T> source, IComparer<T> comparer = null)
        {
            return source.IsOrdered(true, comparer);
        }

        public static bool IsOrdered<T>(this IEnumerable<T> source, bool ascending = true, IComparer<T> comparer = null)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }

            if (comparer == null)
            {
                comparer = Comparer<T>.Default;
            }

            int d = ascending ? 1 : -1;

            Func<T, T, int> compareFunc = (i1, i2) => d * comparer.Compare(i1, i2);
            return IsOrderedImpl(source, compareFunc);
        }

        public static bool IsOrdered<T>(this IEnumerable<T> source, Func<T, T, int> compareFunc)
        {
            if (source == null)
            {
                throw new ArgumentNullException(nameof(source));
            }
            if (compareFunc == null)
            {
                throw new ArgumentNullException(nameof(compareFunc));
            }

            return IsOrderedImpl(source, compareFunc);
        }

        private static bool IsOrderedImpl<T>(this IEnumerable<T> source, Func<T, T, int> compareFunc)
        {
            T prevItem = default(T);
            int i = 0;
            foreach (T item in source)
            {
                if (i == 0)
                {
                    prevItem = item;
                }
                else
                {
                    if (compareFunc(prevItem, item) > 0)
                    {
                        return false;
                    }

                    prevItem = item;
                }

                ++i;
            }

            return true;
        }
    }
}

// References:
// [How do I use LINQ to obtain a unique list of properties from a list of objects?](https://stackoverflow.com/questions/568347/how-do-i-use-linq-to-obtain-a-unique-list-of-properties-from-a-list-of-objects)
// [Test if all values in a list are unique](https://stackoverflow.com/questions/18303897/test-if-all-values-in-a-list-are-unique)
// [Case insensitive 'Contains(string)'](https://stackoverflow.com/questions/444798/case-insensitive-containsstring)
// [Linq IEqualityComparer<string> Ignore Case](https://stackoverflow.com/questions/61175952/linq-iequalitycomparerstring-ignore-case)
// [Linq expression to validate if list is ordered ascending or descending](https://stackoverflow.com/questions/23562150/linq-expression-to-validate-if-list-is-ordered-ascending-or-descending)
// https://github.com/ChangemakerStudios/Papercut-SMTP/blob/develop/src/Papercut.Common/Extensions/EnumerableExtensions.cs
// https://github.com/ChangemakerStudios/Papercut-SMTP/blob/develop/src/Papercut.Common/Extensions/CollectionExtensions.cs
