<Query Kind="Statements" />

var students = new Dictionary<string, int>(StringComparer.InvariantCultureIgnoreCase)
{
    { "Tom", 20 },
	{ "Jerry", 18 },
	{ "Lucy", 22 },
};

Console.WriteLine(students["tom"]);
Console.WriteLine(students["TOM"]);

var studentsV2 = new Dictionary<string, int>
{
    { "Tom", 20 },
	{ "Jerry", 18 },
	{ "Lucy", 22 },
};

var studentsV2LowerCase = studentsV2
    .ToDictionary(kv => kv.Key.ToLower(), kv => kv.Value);
Console.WriteLine(studentsV2LowerCase["tom"]);


// References:
// https://stackoverflow.com/questions/13988643/case-insensitive-dictionary-with-string-key-type-in-c-sharp
