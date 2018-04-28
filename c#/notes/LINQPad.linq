<Query Kind="Statements" />

var currentQueryPath = Util.CurrentQueryPath;
Console.WriteLine(currentQueryPath);

var currentQueryDirectoryName = Path.GetDirectoryName(currentQueryPath);
Console.WriteLine(currentQueryDirectoryName);

typeof(Util).Assembly.Dump();

Console.WriteLine(Directory.GetCurrentDirectory());

Util.Cmd(string.Format("cd /d \"{0}\"", currentQueryDirectoryName));

Console.WriteLine(Directory.GetCurrentDirectory());


// References:
// https://stackoverflow.com/questions/3802779/linqpad-script-directory
// https://stackoverflow.com/questions/8296164/filename-path-of-current-query-in-linqpad
// https://stackoverflow.com/questions/10947422/linqpad-working-directory
// https://stackoverflow.com/questions/3555317/linqpad-extension-methods