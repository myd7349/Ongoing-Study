<Query Kind="Statements" />

Console.WriteLine(Path.GetRelativePath(@"D:\abc\def", @"D:\abc\def\ghi"));
Console.WriteLine(Path.GetRelativePath(@"D:\abc\def\", @"D:\abc\def\ghi"));

// References:
// [How to get relative path from absolute path](https://stackoverflow.com/questions/275689/how-to-get-relative-path-from-absolute-path)
// https://learn.microsoft.com/en-us/dotnet/api/system.io.path.getrelativepath
