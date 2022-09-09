<Query Kind="Statements">
  <Reference Relative="..\Common\bin\Release\Common.dll">F:\myd_backup\Ongoing-Study\c#\Common\bin\Release\Common.dll</Reference>
</Query>

Console.WriteLine(Math.PI);
Console.WriteLine(Math.PI.ToString("0.00"));
Console.WriteLine(Math.PI.ToString("0"));
Console.WriteLine(Math.PI.ToString("F0"));
Console.WriteLine(Math.PI.ToString("F2"));
Console.WriteLine(string.Format("{0,10:0.0}", Math.PI));
Console.WriteLine(string.Format("{0,-10:0.0}", Math.PI));
Console.WriteLine(DoubleConverter.ToExactString(Math.PI));

// References:
// https://stackoverflow.com/questions/9869346/double-string-format
// https://www.csharp-examples.net/string-format-double/
