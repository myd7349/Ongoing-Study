// 2016-06-15T11:12+08:00
using System;
using System.Collections.Generic;
using System.Linq;


namespace Common
{
    public static class ArrayHelper
    {
        public static void Fill<T>(this T[] array, T value)
        {
            if (array == null)
                throw new ArgumentNullException("array");

            for (int i = 0; i < array.Length; i++)
                array[i] = value;
        }

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

        public static T[] Rotate<T>(this T[] array, int rotate)
        {
            if (array == null)
                throw new ArgumentNullException("array");

            if (rotate > 0)
            {
                rotate = array.Length - rotate % array.Length;
            }
            else if (rotate < 0)
            {
                rotate = -rotate;
                rotate %= array.Length;
            }

            if (rotate == 0)
                return (T[])array.Clone();

            return array.Skip(rotate).Concat(array.Take(rotate)).ToArray();
        }
    }
}

// References:
// [Comparing arrays in C#](http://stackoverflow.com/questions/713341/comparing-arrays-in-c-sharp)
// [Easiest way to Rotate a List in c#](https://stackoverflow.com/questions/9948202/easiest-way-to-rotate-a-list-in-c-sharp)
// C# 6.0 in a Nutshell, P298
// > Framework 4.0 introduced one for the purpose of comparing elements in arrays or tuples
//   which you can access via the StructuralComparisons type.
// [StructuralComparisons for arrays](https://stackoverflow.com/questions/32095508/structuralcomparisons-for-arrays)
// [Array.Fill Method](https://docs.microsoft.com/en-us/dotnet/api/system.array.fill?view=net-5.0)
// [How to populate/instantiate a C# array with a single value?](https://stackoverflow.com/questions/1014005/how-to-populate-instantiate-a-c-sharp-array-with-a-single-value)
