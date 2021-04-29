<Query Kind="Program">
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

enum MyColors
{
    Red,
    Green,
    Blue
}

void ParseTest()
{
    Console.WriteLine(MyColors.Red);
    Console.WriteLine(MyColors.Red.ToString());
    
    string colorString = "Red";
    MyColors color = MyColors.Blue;
    if (Enum.TryParse(colorString, out color))
        Console.WriteLine(color);
}


enum Boolean : byte
{
    FALSE = 0,
    TRUE = 1,
}

void GetEnumSize()
{
    try
    {
        Console.WriteLine($"{Marshal.SizeOf(typeof(Boolean))}");
    }
    catch (ArgumentException ex)
    {
        Console.WriteLine($"{ex}");
    }

    Console.WriteLine($"{Marshal.SizeOf(Enum.GetUnderlyingType(typeof(Boolean)))}");
}


void DumpEnumV1(Type type)
{
    if (!type.IsEnum)
        return;

    var values = Enum.GetValues(typeof(Boolean));
    for (int i = 0; i < values.Length; ++i)
    {
        var value = values.GetValue(i);
        try
        {
            // For `enum Boolean : byte`, the following line will raise a InvalidCaseException.
            //var valueAsInteger = (long)value;
            // Instead, you should:
            //var valueAsInteger = Convert.ToInt64(value);
            Console.WriteLine($"{Enum.GetName(typeof(Boolean), value)}: {(long)value}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"{ex}");
        }
    }
}


void DumpEnumV2(Type type)
{
    if (!type.IsEnum)
        return;

    var values = Enum.GetValues(typeof(Boolean));
    for (int i = 0; i < values.Length; ++i)
    {
        var value = values.GetValue(i);
        Console.WriteLine($"{Enum.GetName(typeof(Boolean), value)}: {value} {Convert.ToInt64(value)}");
    }
}


void Main()
{
    ParseTest();
    GetEnumSize();
    DumpEnumV1(typeof(Boolean));
    DumpEnumV2(typeof(Boolean));
}

// References:
// https://stackoverflow.com/questions/23563960/how-to-get-enum-value-by-string-or-int
// https://stackoverflow.com/questions/424366/string-representation-of-an-enum
// [Enum Size in Bytes](https://stackoverflow.com/questions/20944585/enum-size-in-bytes)
// [How do I cast a generic enum to int?](https://stackoverflow.com/questions/16960555/how-do-i-cast-a-generic-enum-to-int)
// [Cast Int to Generic Enum in C#](https://stackoverflow.com/questions/10387095/cast-int-to-generic-enum-in-c-sharp)
// > return (T)(object)value;
