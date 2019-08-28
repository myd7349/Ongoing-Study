<Query Kind="Program">
  <Namespace>System.Collections.Generic</Namespace>
  <Namespace>System.Linq</Namespace>
  <Namespace>System.Reflection</Namespace>
</Query>

[AttributeUsage(AttributeTargets.Field)]
public class OriginalNameAttribute : Attribute
{
    /// <summary>
    /// The name of the element in the .proto file.
    /// </summary>
    public string Name { get; set; }

    /// <summary>
    /// Constructs a new attribute instance for the given name.
    /// </summary>
    /// <param name="name">The name of the element in the .proto file.</param>
    public OriginalNameAttribute(string name)
    {
        Name = CheckNotNull(name, nameof(name));
    }
    
    public static T CheckNotNull<T>(T value, string name) where T : class
    {
        if (value == null)
        {
            throw new ArgumentNullException(name);
        }
        return value;
    }
}

    

static Dictionary<object, string> GetNameMapping(System.Type enumType)
{
    return enumType.GetTypeInfo().DeclaredFields
        .Where(f => f.IsStatic)
        .ToDictionary(f => f.GetValue(null),
                      f => f.GetCustomAttributes<OriginalNameAttribute>()
                           .FirstOrDefault()
                           // If the attribute hasn't been applied, fall back to the name of the field.
                           ?.Name ?? f.Name);
}


enum DataWidth
{
    [OriginalName("DW8Bits")]
    DataWidth8Bits,
    DataWidth16Bits,
    DataWidth32Bits,
}


void Main()
{
    Console.WriteLine(GetNameMapping(typeof(DataWidth)));
}


// References:
// https://github.com/protocolbuffers/protobuf/blob/c60aaf79e63b911b2c04c04e1eacb4f3c36ef790/csharp/src/Google.Protobuf/JsonFormatter.cs#L894-L917

