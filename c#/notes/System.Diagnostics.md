[simple-exec](https://github.com/adamralph/simple-exec)

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

[Output System.Diagnostics.Debug to Console](https://stackoverflow.com/questions/37885587/output-system-diagnostics-debug-to-console)

[Start new process, without being a child of the spawning process](https://stackoverflow.com/questions/8434379/start-new-process-without-being-a-child-of-the-spawning-process)

[Capturing console output from a .NET application (C#)](https://stackoverflow.com/questions/186822/capturing-console-output-from-a-net-application-c)

- https://github.com/slavagu/ConsoleAppLauncher

[How to spawn a process and capture its STDOUT in .NET?](https://stackoverflow.com/questions/285760/how-to-spawn-a-process-and-capture-its-stdout-in-net)

https://github.com/zmjack/NStandard/blob/master/NStandard.Windows/CmdProcess.cs

> ```csharp
> namespace NStandard.Windows
> {
>     [Obsolete("Designing.", false)]
>     public class CmdProcess : IDisposable
>     {
>         public Process Process { get; }
>         public TextWriter OutputRedirect { get; set; }
> 
>         private bool disposedValue;
>         private DateTime lastWriteTime = DateTime.MaxValue;
> 
>         public CmdProcess()
>         {
>             Process = Process.Start(new ProcessStartInfo
>             {
>                 FileName = "cmd",
>                 UseShellExecute = false,
>                 RedirectStandardInput = true,
>                 RedirectStandardError = true,
>                 RedirectStandardOutput = true,
>                 CreateNoWindow = true,
>             });
>             Process.Start();
> 
>             Process.BeginOutputReadLine();
>             Process.BeginErrorReadLine();
>             Process.OutputDataReceived += Process_OutputDataReceived;
>             Process.ErrorDataReceived += Process_ErrorDataReceived;
>         }
> 
>         private void Process_OutputDataReceived(object sender, DataReceivedEventArgs e)
>         {
>             lastWriteTime = DateTime.Now;
>             OutputRedirect?.WriteLine(e.Data);
>         }
> 
>         private void Process_ErrorDataReceived(object sender, DataReceivedEventArgs e)
>         {
>             lastWriteTime = DateTime.Now;
>             OutputRedirect?.WriteLine(e.Data);
>         }
> 
>         // ......
>     }
> }
> ```

https://github.com/wieslawsoltes/Core2D/blob/master/src/Core2D.Modules.Log.Trace/TraceLog.cs

> ```csharp
> using SD = System.Diagnostics;
> 
> namespace Core2D.Modules.Log.Trace;
> 
> public sealed class TraceLog : ILog
> {
>     // ReSharper disable once NotAccessedField.Local
>     private readonly IServiceProvider? _serviceProvider;
> 
>     private const string InformationPrefix = "Information: ";
>     private const string WarningPrefix = "Warning: ";
>     private const string ErrorPrefix = "Error: ";
> 
>     private string? _lastMessage;
>     private SD.TraceListener? _listener;
>     private System.IO.Stream? _stream;
> 
>     public TraceLog(IServiceProvider? serviceProvider)
>     {
>         _serviceProvider = serviceProvider;
>     }
> 
>     public string? LastMessage => _lastMessage;
> 
>     private void SetLastMessage(string message) => _lastMessage = message;
> 
>     public void Initialize(string path)
>     {
>         try
>         {
>             Close();
> 
>             _stream = new System.IO.FileStream(path, System.IO.FileMode.Append);
>             _listener = new SD.TextWriterTraceListener(_stream, "listener");
> 
>             SD.Trace.Listeners.Add(_listener);
>         }
>         catch (Exception ex)
>         {
>             SD.Debug.WriteLine(ex.Message);
>             SD.Debug.WriteLine(ex.StackTrace);
>         }
>     }
> 
>     public void Close()
>     {
>         try
>         {
>             SD.Trace.Flush();
> 
>             if (_listener is { })
>             {
>                 _listener.Dispose();
>                 _listener = null;
>             }
> 
>             if (_stream is { })
>             {
>                 _stream.Dispose();
>                 _stream = null;
>             }
>         }
>         catch (Exception ex)
>         {
>             SD.Debug.WriteLine(ex.Message);
>             SD.Debug.WriteLine(ex.StackTrace);
>         }
>     }
> 
>     public void LogInformation(string message)
>     {
>         SD.Trace.TraceInformation(message);
>         Console.WriteLine(message);
>         SetLastMessage(InformationPrefix + message);
>     }
> 
>     public void LogInformation(string format, params object[] args)
>     {
>         SD.Trace.TraceInformation(format, args);
>         Console.WriteLine(format, args);
>         SetLastMessage(InformationPrefix + string.Format(format, args));
>     }
> 
>     public void LogWarning(string message)
>     {
>         SD.Trace.TraceWarning(message);
>         Console.WriteLine(message);
>         SetLastMessage(WarningPrefix + message);
>     }
> 
>     public void LogWarning(string format, params object[] args)
>     {
>         SD.Trace.TraceWarning(format, args);
>         Console.WriteLine(format, args);
>         SetLastMessage(WarningPrefix + string.Format(format, args));
>     }
> 
>     public void LogError(string message)
>     {
>         SD.Trace.TraceError(message);
>         Console.WriteLine(message);
>         SetLastMessage(ErrorPrefix + message);
>     }
> 
>     public void LogError(string format, params object[] args)
>     {
>         SD.Trace.TraceError(format, args);
>         Console.WriteLine(format, args);
>         SetLastMessage(ErrorPrefix + string.Format(format, args));
>     }
> 
>     public void LogException(Exception ex)
>     {
>         LogError($"{ex.Message}{Environment.NewLine}{ex.StackTrace}");
>         if (ex.InnerException is { })
>         {
>             LogException(ex.InnerException);
>         }
>     }
> 
>     public void Dispose()
>     {
>         Close();
>     }
> }
> ```

[c# open file with default application and parameters](https://stackoverflow.com/questions/11365984/c-sharp-open-file-with-default-application-and-parameters)

```csharp
public static void OpenWithDefaultProgram(string path)
{
    using Process fileopener = new Process();

    fileopener.StartInfo.FileName = "explorer";
    fileopener.StartInfo.Arguments = "\"" + path + "\"";
    fileopener.Start();
}
```

[JpegBitmapEncoder and TLP finally got married](https://modosansreves-coding.blogspot.com/2011/12/jpegbitmapencoder-and-tlp-finally-got.html)

```csharp
static void Main(string[] args)
{
    new Program().Run();

    if (Debugger.IsAttached)
    {
        Console.WriteLine("Press [Enter] to exit...");
        Console.ReadLine();
    }
}
```

[Trying to determine FPS in a C# WPF program](https://stackoverflow.com/questions/4149906/trying-to-determine-fps-in-a-c-sharp-wpf-program)

[How to get Class name that is calling my method?](https://stackoverflow.com/questions/48570573/how-to-get-class-name-that-is-calling-my-method)

[How can I get the assembly file version](https://stackoverflow.com/questions/909555/how-can-i-get-the-assembly-file-version)

```csharp
System.Reflection.Assembly assembly = System.Reflection.Assembly.GetExecutingAssembly();
System.Diagnostics.FileVersionInfo fvi = System.Diagnostics.FileVersionInfo.GetVersionInfo(assembly.Location);
string version = fvi.FileVersion;
```

[Process.start: how to get the output?](https://stackoverflow.com/questions/4291912/process-start-how-to-get-the-output)

```csharp
var proc = new Process 
{
    StartInfo = new ProcessStartInfo
    {
        FileName = "program.exe",
        Arguments = "command line arguments to your executable",
        UseShellExecute = false,
        RedirectStandardOutput = true,
        CreateNoWindow = true
    }
};

proc.Start();
while (!proc.StandardOutput.EndOfStream)
{
    string line = proc.StandardOutput.ReadLine();
    // do something with line
}
```

TraceListener

https://github.com/ElinamLLC/SharpVectors/blob/master/Samples/WpfTestSvgControl/TextBoxTraceListener.cs

[Finding how much memory I can allocate for an array in C#](https://stackoverflow.com/questions/346929/finding-how-much-memory-i-can-allocate-for-an-array-in-c-sharp)

```csharp
Using pc As New System.Diagnostics.PerformanceCounter("Memory", "Available Bytes")
  FreeBytes = pc.NextValue();
End Using
```

[WPF show control in debug mode only](https://stackoverflow.com/questions/2431625/wpf-show-control-in-debug-mode-only)

> Debugger.IsAttached

[How To Debug Data Binding Issues in WPF](https://spin.atomicobject.com/2013/12/11/wpf-data-binding-debug/)

> Debugger.Break()

[Debugging WPF data bindings](https://www.codeproject.com/Articles/244107/Debugging-WPF-data-bindings)

> TextWriterTraceListener

[TraceSwitch and SourceSwitch - what's the difference?](https://stackoverflow.com/questions/3691749/traceswitch-and-sourceswitch-whats-the-difference)

EventLog

https://github.com/microsoft/WPF-Samples/blob/main/Application%20Management/UnhandledExceptionHandling/App.cs

DebuggerDisplayAttribute

[Enhancing Debugging with the Debugger Display Attributes](https://learn.microsoft.com/en-us/dotnet/framework/debug-trace-profile/enhancing-debugging-with-the-debugger-display-attributes)

[Display Subclass of List correctly in Debugger](https://stackoverflow.com/questions/50428305/display-subclass-of-list-correctly-in-debugger)

Debug.Print

[Debug.Print Method](https://learn.microsoft.com/en-us/dotnet/api/system.diagnostics.debug.print?view=netframework-4.7.1)

[Where does System.Diagnostics.Debug.Write output appear?](https://stackoverflow.com/questions/1159755/where-does-system-diagnostics-debug-write-output-appear)

[Automatically log System.diagnostics.trace messages to an Nlog target](https://stackoverflow.com/questions/13260672/automatically-log-system-diagnostics-trace-messages-to-an-nlog-target)

[Routing System.Diagnostics.Trace and System.Diagnostics.TraceSource logs through NLog](https://nlog-project.org/2010/09/02/routing-system-diagnostics-trace-and-system-diagnostics-tracesource-logs-through-nlog.html)

[TraceSource Class](https://learn.microsoft.com/en-us/dotnet/api/system.diagnostics.tracesource?view=net-6.0)

https://github.com/Alex141/CalcBinding/blob/master/CalcBinding/Trace/Tracer.cs

> SourceSwitch

[Which trace source is used by System.Diagnostics.Trace.WriteLine?](https://stackoverflow.com/questions/34491311/which-trace-source-is-used-by-system-diagnostics-trace-writeline)

[Resolving harmless binding errors in WPF](https://weblogs.asp.net/akjoshi/resolving-un-harmful-binding-errors-in-wpf)

```csharp
#if DEBUG
System.Diagnostics.PresentationTraceSources.DataBindingSource.Switch.Level = System.Diagnostics.SourceLevels.Error;
#endif
```

[How to print the current Stack Trace in .NET without any exception?](https://stackoverflow.com/questions/531695/how-to-print-the-current-stack-trace-in-net-without-any-exception)
