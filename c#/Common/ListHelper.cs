namespace Common
{
    using System;
    using System.Collections.Generic;

    public static class ListHelper
    {
        public static bool IsOrdered<T>(this IList<T> list, IComparer<T> comparer = null)
        {
            if (list == null)
                throw new ArgumentNullException(nameof(list));

            if (comparer == null)
                comparer = Comparer<T>.Default;

            if (list.Count > 1)
            {

                for (int i = 1; i < list.Count; ++i)
                {
                    if (comparer.Compare(list[i - 1], list[i]) > 0)
                        return false;
                }
            }

            return true;
        }
    }
}

// References:
// [How to check if a list is ordered?](https://stackoverflow.com/questions/1940214/how-to-check-if-a-list-is-ordered)
