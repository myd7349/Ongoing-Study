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
