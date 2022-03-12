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

https://github.com/wieslawsoltes/Core2D/blob/master/src/Core2D/Modules/Log.Trace/TraceLog.cs

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

