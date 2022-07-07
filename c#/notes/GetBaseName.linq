<Query Kind="Statements" />

Console.WriteLine(Path.GetDirectoryName(@"D:\1\2\3"));
Console.WriteLine(Path.GetDirectoryName(@"D:\1\2\3\"));

Console.WriteLine(Path.GetFileName(@"D:\1\2\3"));
Console.WriteLine(Path.GetFileName(@"D:\1\2\3\"));

Console.WriteLine(GetBaseName(@"D:\1\2\3"));
Console.WriteLine(GetBaseName(@"D:\1\2\3\"));

Console.WriteLine(GetBaseNameV2(@"D:\1\2\3"));
Console.WriteLine(GetBaseNameV2(@"D:\1\2\3\"));

static string GetBaseName(string path)
{
    if (path == null)
        throw new ArgumentNullException(nameof(path));

    path = path.TrimEnd(Path.DirectorySeparatorChar)
        .TrimEnd(Path.AltDirectorySeparatorChar);
    return Path.GetFileName(path);
}

static string GetBaseNameV2(string path)
{
    if (path == null)
        throw new ArgumentNullException(nameof(path));

    return new DirectoryInfo(path).Name;
}


// References:
// [Get the (last part of) current directory name in C#](https://stackoverflow.com/questions/6018293/get-the-last-part-of-current-directory-name-in-c-sharp)
