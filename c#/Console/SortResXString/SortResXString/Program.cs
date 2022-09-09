using System.Collections;

using System.Resources.NetStandard;

internal class Program
{
    static void Main(string[] args)
    {
        if (args.Length != 3)
        {
            Console.WriteLine("Usage: SortResXString <reference .resx file> <input .resx file>");
            return;
        }

        var originalStrings = ReadStrings(args[1]);

        var stringsToBeSorted = ReadStrings(args[2]).Values.OrderBy(si => originalStrings[si.Item2].Item1);
        foreach (var str in stringsToBeSorted)
        {
            Console.WriteLine($@"  <data name=""{str.Item2}"" xml:space=""preserve"">
    <value>{str.Item3}</value>
  </data>");
        }
    }

    // Read string resource from .resx file.
    static Dictionary<string, Tuple<int, string, string?>> ReadStrings(string resxFilePath)
    {
        var strings = new Dictionary<string, Tuple<int, string, string?>>();

        using (var resxReader = new ResXResourceReader(resxFilePath))
        {
            int count = 0;
            
            foreach (DictionaryEntry entry in resxReader)
            {
                strings[entry.Key.ToString()!] = Tuple.Create(
                    ++count,
                    entry.Key.ToString()!,
                    entry.Value?.ToString());
            }
        }

        return strings;
    }
}


// References:
// [How to Save Console.WriteLine Output to Text File](https://stackoverflow.com/questions/4470700/how-to-save-console-writeline-output-to-text-file)
// [Alternative for ResxResourceWriter in .NET Core](https://stackoverflow.com/questions/42199015/alternative-for-resxresourcewriter-in-net-core)
// [Move ResXResourceReader and ResXResourceSet from System.Windows.Forms to System.Runtime](https://github.com/dotnet/runtime/issues/47795)
// [How to sort an array containing class objects by a property value of a class instance?](https://stackoverflow.com/questions/1304278/how-to-sort-an-array-containing-class-objects-by-a-property-value-of-a-class-ins)
// [How to sort a list of objects by a specific field in C#?](https://stackoverflow.com/questions/1301822/how-to-sort-a-list-of-objects-by-a-specific-field-in-c)
// https://github.com/rocksdanister/lively-translations
