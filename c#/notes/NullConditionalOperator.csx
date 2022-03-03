string s = null;
Console.WriteLine("{0}", s?.Length);
if (s.Length > 0)
    Console.WriteLine("Hello, world!");
Console.WriteLine(null > 0);
Console.WriteLine(null < 0);
Console.WriteLine(null != 0);
Console.WriteLine(null == 0);

// References:
// [How does comparison operator works with null int?](https://stackoverflow.com/questions/15777745/how-does-comparison-operator-works-with-null-int)
// > When you perform comparisons with nullable types, if the value of one of the nullable types is null and the other is not, all comparisons evaluate to false except for !=
