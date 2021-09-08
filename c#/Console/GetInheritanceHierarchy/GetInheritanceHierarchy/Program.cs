namespace GetInheritanceHierarchy
{
    using System;

    using Common;

    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                var typeName = Console.ReadLine();
                if (typeName == "Q")
                    break;

                if (string.IsNullOrWhiteSpace(typeName))
                    continue;

                Type type;
                if (TypeHelper.KnownTypes.ContainsKey(typeName))
                {
                    type = TypeHelper.KnownTypes[typeName];
                }
                else
                {
                    try
                    {
                        type = Type.GetType(typeName);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Type.GetType(\"{0}\") failed: {1}\n{2}",
                            typeName, ex.GetType(), ex);
                        type = null;
                    }
                }

                if (type != null)
                {
                    foreach (var baseType in type.GetInheritanceHierarchy())
                        Console.WriteLine(baseType);
                }
                else
                {
                    Console.WriteLine("Type.GetType(\"{0}\") returned null.", typeName);
                }
            }
        }
    }
}

// References:
// [Convert String to Type in C#](https://stackoverflow.com/questions/11107536/convert-string-to-type-in-c-sharp)
