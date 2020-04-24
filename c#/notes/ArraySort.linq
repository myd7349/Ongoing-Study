<Query Kind="Program" />

public static class ListHelper
{
    public static bool IsOrdered<T>(this IList<T> list, IComparer<T> comparer = null)
    {
        if (list == null)
            throw new ArgumentNullException("list");

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
        
static Dictionary<string, int> NumberOrders = new Dictionary<string, int>(StringComparer.InvariantCultureIgnoreCase)
{
    { "One", 1 },
    { "Two", 2 },
    { "Three", 3 },
    { "Four", 4 },
    { "Five", 5 },
    { "Six", 6 },
};
    
static bool IsNormalNumberOrder(string[] numbers)
{
    return numbers.TakeWhile(lead => !string.IsNullOrWhiteSpace(lead))
        .Select(lead => NumberOrders[lead])
        .ToList()
        .IsOrdered();
}
        
class NumberComparer : IComparer<string>
{
    int IComparer<string>.Compare(string x, string y)
    {
        return Comparer<int>.Default.Compare(NumberOrders[x], NumberOrders[y]);
    }
}

void Main()
{   
    var data = new double[][]
    {
        new double[] { 3, 33, 333, 3333 },
        new double[] { 4, 44, 444, 4444 },
        new double[] { 1, 11, 111, 1111 },
        new double[] { 2, 22, 222, 2222 },
    };
    
    var dataOrder = new string[]
    {
        "three", "four", "one", "two",
    };
    
    var sortedDataOrder = (string[])dataOrder.Clone();
    Array.Sort(sortedDataOrder, new NumberComparer());
    Console.WriteLine(sortedDataOrder);
    
    var sortedData = new double[data.Length][];
    for (int i = 0; i < data.Length; ++i)
        sortedData[i] = data[Array.IndexOf(dataOrder, sortedDataOrder[i])];
    
    Console.WriteLine(dataOrder);
    Console.WriteLine(IsNormalNumberOrder(dataOrder));
    Console.WriteLine(sortedDataOrder);
    Console.WriteLine(IsNormalNumberOrder(sortedDataOrder));
    
    Console.WriteLine(sortedData);
}
