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
    }
}

// References:
// [How do I use LINQ to obtain a unique list of properties from a list of objects?](https://stackoverflow.com/questions/568347/how-do-i-use-linq-to-obtain-a-unique-list-of-properties-from-a-list-of-objects)
// [Test if all values in a list are unique](https://stackoverflow.com/questions/18303897/test-if-all-values-in-a-list-are-unique)
// [Case insensitive 'Contains(string)'](https://stackoverflow.com/questions/444798/case-insensitive-containsstring)
// [Linq IEqualityComparer<string> Ignore Case](https://stackoverflow.com/questions/61175952/linq-iequalitycomparerstring-ignore-case)
