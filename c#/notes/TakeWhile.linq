<Query Kind="Statements" />

var names = new string[]
{
    "Tom",
	null,
	"Jerry",
	"Lucy",
	"",
	"John",
};

foreach (var name in names.TakeWhile(name => !string.IsNullOrWhiteSpace(name)))
    Console.WriteLine(name);

foreach (var name in names.Where(name => !string.IsNullOrWhiteSpace(name)))
    Console.WriteLine(name);

// References:
// https://stackoverflow.com/questions/12397880/using-linq-how-to-select-conditionally-some-items-but-when-no-conditions-select
