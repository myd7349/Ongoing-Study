Libraries:

- [NLog](https://github.com/NLog/NLog)
- [serilog](https://github.com/serilog/serilog)
  - [serilog-sinks-http](https://github.com/FantasticFiasco/serilog-sinks-http)
  - [logging-dotnet](https://github.com/felfel/logging-dotnet)
- [common-logging](https://github.com/net-commons/common-logging)
  - https://github.com/itext/itext7-dotnet
- [MSBuildStructuredLog](https://github.com/KirillOsenkov/MSBuildStructuredLog)
- https://github.com/Catel/Catel

[When should I use Tracing vs Logger.NET, Enterprise Library, log4net or Ukadc.Diagnostics?](https://stackoverflow.com/questions/4775194/when-should-i-use-tracing-vs-logger-net-enterprise-library-log4net-or-ukadc-di)

https://github.com/cyanfish/naps2/tree/9ffd24bb4186b7a81d4f1d686ee946d2684e8239/NAPS2.Core/Logging

https://github.com/microsoft/FASTER

[When logging when is an error fatal?](https://stackoverflow.com/questions/313351/when-logging-when-is-an-error-fatal)

https://github.com/de4dot/de4dot/blob/master/de4dot.code/Logger.cs

[LogParser](https://en.wikipedia.org/wiki/Logparser)

- https://github.com/TerribleDev/TimberWinR

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

https://github.com/Analogy-LogViewer/Analogy.LogViewer
