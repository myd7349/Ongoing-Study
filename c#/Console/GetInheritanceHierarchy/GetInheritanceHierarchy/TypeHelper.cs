namespace GetInheritanceHierarchy
{
    using System;
    using System.Collections.Generic;

    public static class TypeHelper
    {
        static TypeHelper()
        {
            KnownTypes = new Dictionary<string, Type>();

            KnownTypes["int"] = typeof(int);
            KnownTypes["double"] = Type.GetType("System.Double");
            KnownTypes["string"] = Type.GetType("System.String");
        }

        public static IEnumerable<Type> GetInheritanceHierarchy(this Type type)
        {
            for (var current = type; current != null; current = current.BaseType)
                yield return current;
        }

        public static readonly Dictionary<string, Type> KnownTypes;
    }
}

// References:
// [Get inheritance tree of type](https://stackoverflow.com/questions/5716896/get-inheritance-tree-of-type)
// [Convert String to Type in C#](https://stackoverflow.com/questions/11107536/convert-string-to-type-in-c-sharp)
