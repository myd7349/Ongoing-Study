<Query Kind="Statements" />

short i = 123;

Console.WriteLine((double)i);

try
{
    Console.WriteLine((double)(object)i);
}
catch (InvalidCastException ex)
{
    Console.WriteLine(ex);
}
