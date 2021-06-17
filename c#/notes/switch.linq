<Query Kind="Program" />

class Example
{
    static void Main(string[] args)
    {
        int[] values = { 2, 4, 6, 8, 10 };
        ShowCollectionInformation(values);

        var names = new List<string>();
        names.AddRange(new string[] { "Adam", "Abigail", "Bertrand", "Bridgette" });
        ShowCollectionInformation(names);

        List<int> numbers = null;
        ShowCollectionInformation(numbers);
    }

    private static void ShowCollectionInformation<T>(T coll)
    {
        switch (coll)
        {
            case Array arr:
               Console.WriteLine($"An array with {arr.Length} elements.");
               break;
            case IEnumerable<int> ieInt:
               Console.WriteLine($"Average: {ieInt.Average(s => s)}");
               break;
            case IList list:
               Console.WriteLine($"{list.Count} items");
               break;
            case IEnumerable ie:
               string result = "";
               foreach (var e in ie)
                  result += $"{e} ";
               Console.WriteLine(result);
               break;
            case object o:
               Console.WriteLine($"A instance of type {o.GetType().Name}");
               break;
            default:
                Console.WriteLine("Null passed to this method.");
                break;
        }
    }
}

// References:
// [switch (C# reference)](https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/keywords/switch)
