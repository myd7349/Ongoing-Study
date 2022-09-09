[Share nlog config with multiple projects and the proper threadsafe way to all write to the same log file?](https://stackoverflow.com/questions/13854426/share-nlog-config-with-multiple-projects-and-the-proper-threadsafe-way-to-all-wr)

[How to use NLog from multiple projects in the same solution](https://stackoverflow.com/questions/29188721/how-to-use-nlog-from-multiple-projects-in-the-same-solution)

[Adding method name in NLog](https://stackoverflow.com/questions/21949078/adding-method-name-in-nlog)

[AsyncTargetWrapper Class](https://nlog-project.org/documentation/v2.0.1/html/T_NLog_Targets_Wrappers_AsyncTargetWrapper.htm#:~:text=You%20should%20wrap%20targets%20that%20spend%20a%20non-trivial,to%20the%20%3Ctargets%2F%3E%20element%20in%20the%20configuration%20file.)

> ```c#
> using NLog;
> using NLog.Targets;
> using NLog.Targets.Wrappers;
> using System.Text;
> 
> class Example
> {
>     static void Main(string[] args)
>     {
>         FileTarget target = new FileTarget();
>         target.Layout = "${longdate} ${logger} ${message}";
>         target.FileName = "${basedir}/logs/logfile.txt";
>         target.KeepFileOpen = false;
>         target.Encoding = Encoding.UTF8;
> 
>         AsyncTargetWrapper wrapper = new AsyncTargetWrapper();
>         wrapper.WrappedTarget = target;
>         wrapper.QueueLimit = 5000;
>         wrapper.OverflowAction = AsyncTargetWrapperOverflowAction.Discard;
> 
>         NLog.Config.SimpleConfigurator.ConfigureForTargetLogging(wrapper, LogLevel.Debug);
> 
>         Logger logger = LogManager.GetLogger("Example");
>         logger.Debug("log message");
> 
>         wrapper.Flush();
>     }
> }
> ```

[AsyncWrapper target](https://github.com/nlog/NLog/wiki/AsyncWrapper-target)

[Logging in multiple files using NLog](https://stackoverflow.com/questions/20352325/logging-in-multiple-files-using-nlog)

[Why do loggers recommend using a logger per class?](https://stackoverflow.com/questions/3143929/why-do-loggers-recommend-using-a-logger-per-class)

[How to make NLog terminate application on fatal errors?](https://stackoverflow.com/questions/19225402/how-to-make-nlog-terminate-application-on-fatal-errors)

https://github.com/microsoft/Vipr/blob/master/src/Core/Vipr/NLog.config

[LineEnding](https://nlog-project.org/documentation/v4.4.0/html/P_NLog_Targets_FileTarget_LineEnding.htm)

[Using NLog with WPF richtextbox](https://stackoverflow.com/questions/48809045/using-nlog-with-wpf-richtextbox)

[How can I use a RichTextBox as a NLog Target in a WPF application?](https://stackoverflow.com/questions/6617689/how-can-i-use-a-richtextbox-as-a-nlog-target-in-a-wpf-application)

https://github.com/erizet/NlogViewer

[How to tell NLog to log exceptions? - Stack Overflow](https://stackoverflow.com/questions/9199073/how-to-tell-nlog-to-log-exceptions)

[How to format NLog exception output to get a line separator?](https://stackoverflow.com/questions/44654276/how-to-format-nlog-exception-output-to-get-a-line-separator)

> ```xml
> layout="-------------------------------------------------------------- 
>      ${newline}${date:universalTime=false:format=yyyy-MM-dd HH\:mm\:ss}| 
>        ${aspnet- session:Variable=SessionKey} ${message} | 
>        ${exception:format=type,message,StackTrace}" 
>        fileName="${basedir}/App_Data/Log/ 
>        ${date:universalTime=false:format=yyyyMMdd}.log"
> ```

[Log Header is printed only once per file · Issue #1713 · NLog/NLog · GitHub](https://github.com/NLog/NLog/issues/1713)

> ```xml
> <?xml version="1.0" encoding="utf-8" ?>
> <nlog xmlns="http://www.nlog-project.org/schemas/NLog.xsd"
>       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
>       xsi:schemaLocation="http://www.nlog-project.org/schemas/NLog.xsd NLog.xsd"
>       autoReload="true"
>       throwExceptions="false"
>       internalLogLevel="Off"
>       internalLogFile="c:\temp\nlog-internal.log">
> 
>     <targets xsi:type="NLogTargets" async="false">
> 
>         <target xsi:type="File"
>                 name="fileTarget"
>                 fileName="${basedir}/logs/SvnBootstrapper.log"
>                 lineEnding="CRLF"
>                 archiveAboveSize="5048576"
>                 maxArchiveFiles="1"
>                 archiveNumbering="Rolling"
>                 header="${newline}
> ======================================================================================================================================================${newline}
> Logging start = ${longdate}${newline}
> Base dirctory = ${basedir}${newline}
> Machine name  = ${machinename}${newline}
> ------------------------------------------------------------------------------------------------------------------------------------------------------${newline}
> Date and Time            | Level | Module                                                | Message${newline}
> ------------------------------------------------------------------------------------------------------------------------------------------------------"
>                 layout=" ${longdate} | ${level:uppercase=true:padding=-5} | ${Logger:shortName=true:padding=20} | ${callsite:includeSourcePath=false:className=false:padding=30:fixedLength=true} | ${message} ${exception:format=message}"
>                 footer="${newline}
> ------------------------------------------------------------------------------------------------------------------------------------------------------${newline}
> Logging end   = ${longdate}${newline}
> ======================================================================================================================================================" />
>     </targets>
> 
>     <rules>
> 
>         <logger name="*" minlevel="Info" writeTo="fileTarget" />
> 
>     </rules>
> </nlog>
> ```

Log exception V1:

```xml
<target xsi:type="File" name="logFile" fileName="${basedir}/Logs/${shortdate}.log"
        layout="${longdate} ${level:uppercase=false:padding=-5}: ${message} {exception:format=tostring}"
        optimizeBufferReuse="true" />
```

Log exception V2:

```xml
<target xsi:type="File" name="logFile" fileName="${basedir}/Logs/${shortdate}.log"
        layout="${longdate} ${level:uppercase=false:padding=-5}: ${message}${newline}${exception:format=tostring}"
        optimizeBufferReuse="true" />
```

Log exception V3, doesn't work as expected:

```xml
<target xsi:type="File" name="logFile" fileName="${basedir}/Logs/${shortdate}.log"
        layout="${longdate} ${level:uppercase=false:padding=-5}: ${message}{exception:format=newline,tostring}"
        optimizeBufferReuse="true" />
```

https://www.nuget.org/packages/NLog.IndentException

[Newline in exception formatt · Issue #2248 · NLog/NLog · GitHub](https://github.com/NLog/NLog/issues/2248)

> ```xml
> ${exception:format=tostring,data:maxInnerExceptionLevel=10:separator=\r\n}
> ```

[Nlog output characters if exception not null](https://stackoverflow.com/questions/34139072/nlog-output-characters-if-exception-not-null)

> ```xml
> <variable name="StdLayout" 
> value="${longdate} | ${level} | ${logger} | ${message:exceptionSeparator= }${exception:format=tostring}" />
> ```

Log exception V3, doesn't work as expected:

```xml
<target xsi:type="File" name="logFile" fileName="${basedir}/Logs/${shortdate}.log"
        layout="${longdate} ${level:uppercase=false:padding=-5}: ${message}${message:exceptionSeparator=${newline}}{exception:format=tostring}"
        optimizeBufferReuse="true" />
```

[Console application not logging error with NLOG in AppDomain.CurrentDomain.UnhandledException](https://stackoverflow.com/questions/71415635/console-application-not-logging-error-with-nlog-in-appdomain-currentdomain-unhan)

```csharp
using System;
using NLog;
using NLog.Targets;

namespace ConsoleDBLog;

internal static class Program
{
    private static ILogger? _logger;

    static void UnhandledExceptionTrapper(object sender, UnhandledExceptionEventArgs e)
    {
        _logger?.Error((Exception?) e.ExceptionObject, "unhandled exception");
        LogManager.Shutdown();
    }

    private static void Main()
    {
        SetupDB_NLOG();
        _logger = LogManager.GetCurrentClassLogger();
        AppDomain.CurrentDomain.UnhandledException += UnhandledExceptionTrapper;
        throw new Exception("test");
    }

    static void SetupDB_NLOG()
    {
        DatabaseTarget target = new DatabaseTarget();
        target.Name = "nlog-db";

        target.DBProvider = "Npgsql.NpgsqlConnection, Npgsql";
        target.ConnectionString = "Server=127.0.0.1;Port=5432;User Id=stephan;Password=;Database=stephan;";
        target.CommandText =
            "insert into \"public\".\"log_table\"(time_stamp,level,logger,message,stacktrace) values(CAST(@time_stamp AS timestamp),@level,@logger,@message,@stacktrace);";

        var param = new DatabaseParameterInfo
        {
            Name = "@time_stamp",
            Layout = "${date:format=yyyy-MM-ddTHH\\:mm\\:ss.fff}"
        };
        target.Parameters.Add(param);

        param = new DatabaseParameterInfo
        {
            Name = "@level",
            Layout = "${level}"
        };
        target.Parameters.Add(param);

        param = new DatabaseParameterInfo
        {
            Name = "@logger",
            Layout = "${logger}"
        };
        target.Parameters.Add(param);

        param = new DatabaseParameterInfo
        {
            Name = "@message",
            Layout = "${message}"
        };
        target.Parameters.Add(param);

        param = new DatabaseParameterInfo
        {
            Name = "@stacktrace",
            Layout = "${exception:format=stacktrace}"
        };
        target.Parameters.Add(param);

        NLog.Config.SimpleConfigurator.ConfigureForTargetLogging(target, LogLevel.Debug);

        //Uncomment the following lines to see things that would silently fail and
        //to get more diagnostic debug output about what is actually running.
        
        // InternalLogger.LogToConsole = true;
        // InternalLogger.LogLevel = LogLevel.Trace;
        // LogManager.ThrowExceptions = true;

        // LogManager.GetCurrentClassLogger().Debug("test logging");
        // LogManager.Flush();
    }
}
```

[NLog configured to automatically log all exceptions?](https://stackoverflow.com/questions/13895929/nlog-configured-to-automatically-log-all-exceptions)

[Automatically log System.diagnostics.trace messages to an Nlog target](https://stackoverflow.com/questions/13260672/automatically-log-system-diagnostics-trace-messages-to-an-nlog-target)

[How to route System.Diagnostics.TraceSource logs through NLog in .NET Core](https://stackoverflow.com/questions/40052355/how-to-route-system-diagnostics-tracesource-logs-through-nlog-in-net-core)

[Routing System.Diagnostics.Trace and System.Diagnostics.TraceSource logs through NLog](https://nlog-project.org/2010/09/02/routing-system-diagnostics-trace-and-system-diagnostics-tracesource-logs-through-nlog.html)

[Which trace source is used by System.Diagnostics.Trace.WriteLine?](https://stackoverflow.com/questions/34491311/which-trace-source-is-used-by-system-diagnostics-trace-writeline)

[Force NLog to create a new log folder for year, month and day](https://stackoverflow.com/questions/6685659/force-nlog-to-create-a-new-log-folder-for-year-month-and-day)

```xml
<target name="logFile" xsi:type="File" fileName="${basedir}/Logs/${date:format=yyyy}/${shortdate}.log"
        layout="${longdate}|${level:uppercase=false:padding=-5}|${appdomain} - ${callsite-filename}(${callsite-linenumber}) - ${callsite:methodName=false}> ${message} ${onexception:${exception:format=tostring} ${newline} ${stacktrace} ${newline}"
        maxArchiveFiles="30" />
```

[NLog settings not deleting MaxArchiveDays or MaxArchiveFiles?](https://stackoverflow.com/questions/61347861/nlog-settings-not-deleting-maxarchivedays-or-maxarchivefiles)
