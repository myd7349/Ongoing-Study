[How do I specify the exit code of a console application in .NET?](https://stackoverflow.com/questions/155610/how-do-i-specify-the-exit-code-of-a-console-application-in-net)

[Show/Hide the console window of a C# console application](https://stackoverflow.com/questions/3571627/show-hide-the-console-window-of-a-c-sharp-console-application)

[.NET Global exception handler in console application](https://stackoverflow.com/questions/3133199/net-global-exception-handler-in-console-application)

> ```c#
> using System;
> 
> class Program {
>     static void Main(string[] args) {
>         System.AppDomain.CurrentDomain.UnhandledException += UnhandledExceptionTrapper;
>         throw new Exception("Kaboom");
>     }
> 
>     static void UnhandledExceptionTrapper(object sender, UnhandledExceptionEventArgs e) {
>         Console.WriteLine(e.ExceptionObject.ToString());
>         Console.WriteLine("Press Enter to continue");
>         Console.ReadLine();
>         Environment.Exit(1);
>     }
> }
> ```

[pythonw.exe or python.exe?](https://stackoverflow.com/questions/9705982/pythonw-exe-or-python-exe)

> pythonw.exe is a GUI app for launching GUI/no-UI-at-all scripts.
>
> - NO console window is opened.
> - Execution is asynchronous: 

[AttachConsole() shows data on pipe but the > operator doesn't correctly redirect to file](https://stackoverflow.com/questions/11523595/attachconsole-shows-data-on-pipe-but-the-operator-doesnt-correctly-redirect)

>  If you launch your application from a console you'll notice that any output appears after the next prompt. You can avoid this with start /wait.
