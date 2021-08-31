https://dotnetfiddle.net/

https://dotnetfiddle.net/wrcAxr

> ```csharp
> // @nuget: CommandLineParser -Version 2.7.82
> using System;
> using System.Collections.Generic;
> using CommandLine;
> using System.Linq;
> 
> 
> public class Program
> {
> 	public static void Main()
> 	{
> 		var text = "subCommand file=filename.txt verbose simulate";
> 		var args = text.Split();
> 		var result = CommandLine.Parser.Default.ParseArguments<Options>(args).MapResult((opts) => RunOptionsAndReturnExitCode(opts), //in case parser sucess
>  errs => HandleParseError(errs)); //in  case parser fail
> 		Console.WriteLine("Return code= {0}", result);
> 	}
> 
> 	//3)	//In sucess: the main logic to handle the options
> 	static int RunOptionsAndReturnExitCode(Options o)
> 	{
> 		Console.WriteLine("Success");
> 		var exitCode = 0;
> 		var props = o.Props;
> 		//foreach (var prop in props)
> 		Console.WriteLine("props= {0}", string.Join(",", props));
> 		return exitCode;
> 	}
> 
> 	//in case of errors or --help or --version
> 	static int HandleParseError(IEnumerable<Error> errs)
> 	{
> 		var result = -2;
> 		Console.WriteLine("errors {0}", errs.Count());
> 		if (errs.Any(x => x is HelpRequestedError || x is VersionRequestedError))
> 			result = -1;
> 		Console.WriteLine("Exit code {0}", result);
> 		return result;
> 	}
> }
> 
> class Options
> {
> 	[Value(0)]
> 	public IEnumerable<string> Props
> 	{
> 		get;
> 		set;
> 	}
> }
> ```



