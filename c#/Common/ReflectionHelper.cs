using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace Common
{
    public static class ReflectionHelper
    {
        public static IEnumerable<T2> GetNonPublicFields<T2, T>(this T t)
            where T : class
            where T2 : class
        {
            var fields = typeof(T).GetFields(BindingFlags.NonPublic | BindingFlags.Instance);
            return fields
                .Where(fi => fi.FieldType == typeof(T2))
                .Select(fi => fi.GetValue(t) as T2);
        }

        public static object GetNonPublicField<T>(this T t, string name)
            where T : class
        {
            if (string.IsNullOrWhiteSpace(name))
                throw new ArgumentException(nameof(name));

            var field = typeof(T).GetField(name, BindingFlags.NonPublic | BindingFlags.Instance);
            return field?.GetValue(t);
        }
    }
}


// References:
// [Find a private field with Reflection?](https://stackoverflow.com/questions/95910/find-a-private-field-with-reflection)
