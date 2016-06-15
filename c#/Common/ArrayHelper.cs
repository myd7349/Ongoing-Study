// 2016-06-15T11:12+08:00
using System.Collections.Generic;


namespace Common
{
    public static class ArrayHelper
    {
        public static bool EqualTo<T>(this T[] lhs, T[] rhs)
        {
            if (ReferenceEquals(lhs, rhs))
                return true;

            if (lhs == null || rhs == null)
                return false;

            if (lhs.Length != rhs.Length)
                return false;

            EqualityComparer<T> comparer = EqualityComparer<T>.Default;
            for (int i = 0; i < lhs.Length; i++)
            {
                if (!comparer.Equals(lhs[i], rhs[i]))
                    return false;
            }

            return true;
        }
    }
}

// References:
// [Comparing arrays in C#](http://stackoverflow.com/questions/713341/comparing-arrays-in-c-sharp)
