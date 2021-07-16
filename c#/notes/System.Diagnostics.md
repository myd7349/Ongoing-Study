[Trace vs Debug in .NET BCL](https://stackoverflow.com/questions/179868/trace-vs-debug-in-net-bcl)

[Trace to a file](https://stackoverflow.com/questions/7769085/net-trace-to-a-file-not-working)

[How to send the tracing output to a file in the file system?](https://stackoverflow.com/questions/3279992/how-to-send-the-tracing-output-to-a-file-in-the-file-system)

[Environment.TickCount vs DateTime.Now vs Stopwatch](https://stackoverflow.com/questions/243351/environment-tickcount-vs-datetime-now)

[How can I get the assembly file version](https://stackoverflow.com/questions/909555/how-can-i-get-the-assembly-file-version)
```csharp
System.Reflection.Assembly assembly = System.Reflection.Assembly.GetExecutingAssembly();
System.Diagnostics.FileVersionInfo fvi = System.Diagnostics.FileVersionInfo.GetVersionInfo(assembly.Location);
string version = fvi.FileVersion;
```

[Enable code on Release compilation](https://stackoverflow.com/questions/6927263/enable-code-on-release-compilation)

> ```csharp
> #if !DEBUG
> 
> // Release-only code goes here...
> 
> #endif
> ```

