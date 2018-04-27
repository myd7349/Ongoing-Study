<Query Kind="Statements" />

var path = Path.Combine(@"C:\Program Files\MyApp\data", @"..\");
Console.WriteLine("App path: {0}", path);
// Normalize path
Console.WriteLine("Normalized App path: {0}", Path.GetFullPath(path));

var path2 = @"C://Program Files\\MyApp\\";
Console.WriteLine("App path: {0}", path2);
Console.WriteLine("Normalized App path: {0}", Path.GetFullPath(path2));


// References:
// https://stackoverflow.com/questions/1266674/how-can-one-get-an-absolute-or-normalized-file-path-in-net
// https://stackoverflow.com/questions/5292305/is-there-a-c-sharp-equivalent-of-pythons-os-path-normpath
