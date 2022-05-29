// 2016-09-29T17:26+08:00
using System;
using System.IO;
using System.Reflection;


namespace GetApplicationPath
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(Directory.GetCurrentDirectory());
            Console.WriteLine(Path.GetDirectoryName(Environment.GetCommandLineArgs()[0]));
            Console.WriteLine(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location));
            Console.WriteLine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));
            Console.WriteLine(AppDomain.CurrentDomain.BaseDirectory);
            Console.WriteLine(Common.Util.GetAppPath());
            Console.WriteLine(System.Windows.Forms.Application.StartupPath);

            Common.Util.Pause();
        }
    }
}

// References:
// [Get current folder path](http://stackoverflow.com/questions/15653921/get-current-folder-path)
// [mono c# get application path](http://stackoverflow.com/questions/6246074/mono-c-sharp-get-application-path/18562036#18562036)
// C# 6.0 in a Nutshell, P631
// https://github.com/microsoft/perfview/blob/7bc1b55ebf6773f8afcdf46a96d2e9ccc763aeee/src/HeapDump/Program.cs#L27-L29
//            var exeAssembly = System.Reflection.Assembly.GetExecutingAssembly();
//            var parentDir = Path.GetDirectoryName(Path.GetDirectoryName(exeAssembly.ManifestModule.FullyQualifiedName));
//            string fileName = Path.Combine(parentDir, simpleName + ".dll");
// https://github.com/commandlineparser/commandline/blob/master/src/CommandLine/Infrastructure/ReflectionHelper.cs
//        private static Assembly GetExecutingOrEntryAssembly()
//        {
//            //resolve issues of null EntryAssembly in Xunit Test #392,424,389
//            //return Assembly.GetEntryAssembly();
//            return Assembly.GetEntryAssembly() ?? Assembly.GetCallingAssembly();
//        }
// https://github.com/ElinamLLC/SharpVectors/blob/master/Source/SharpVectorCore/Utils/PathUtils.cs
//     AppContext.BaseDirectory;
// [Load local HTML file in a C# WebBrowser](https://stackoverflow.com/questions/7194851/load-local-html-file-in-a-c-sharp-webbrowser)
//     Application.ExecutablePath
// https://github.com/AgigoNoTana/HiddenDesktopViewer/blob/master/HiddenDesktopViewer/Form1.cs
// https://github.com/ChangemakerStudios/Papercut-SMTP/blob/develop/src/Papercut.Common/Helper/PathHelpers.cs
//     string filePath = new Uri(assembly.CodeBase).LocalPath;
// [6 ways to get the current directory in C#](https://yetanotherchris.dev/csharp/6-ways-to-get-the-current-directory-in-csharp/)
// - System.AppContext.BaseDirectory
// - AppDomain.CurrentDomain.BaseDirectory
// - Directory.GetCurrentDirectory()
// - Environment.CurrentDirectory
// - Assembly.Location
// - Application.StartupPath(WinForms)
// - Application.ExecutablePath
// [C#获取当前程序运行路径的方法集合](https://www.cnblogs.com/xifengyeluo/p/8409050.html)
// - this.GetType().Assembly.Location;
// - System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
// - System.Environment.CurrentDirectory;
// - System.AppDomain.CurrentDomain.BaseDirectory;
// - System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
// - System.Windows.Forms.Application.StartupPath;
// - System.Windows.Forms.Application.ExecutablePath;
// - System.IO.Directory.GetCurrentDirectory();

/*
Application: CoilQueryTool.exe
CoreCLR Version: 6.0.522.21309
.NET Version: 6.0.5
Description: The process was terminated due to an unhandled exception.
Exception Info: System.ArgumentNullException: Value cannot be null. (Parameter 'path1')
   at System.IO.Path.Combine(String path1, String path2)
   at CoilQueryTool.Common.ConfigBase`1.get_ConfigFilePath() in C:\Users\myd7349\Desktop\CoilQueryTool\WPF\CoilQueryTool\CoilQueryTool\Common\ConfigFileBase.cs:line 98
   at CoilQueryTool.Common.ConfigBase`1.Load() in C:\Users\myd7349\Desktop\CoilQueryTool\WPF\CoilQueryTool\CoilQueryTool\Common\ConfigFileBase.cs:line 29
   at CoilQueryTool.App.ConfigureServices() in C:\Users\myd7349\Desktop\CoilQueryTool\WPF\CoilQueryTool\CoilQueryTool\App.xaml.cs:line 29
   at CoilQueryTool.App.OnStartup(StartupEventArgs e) in C:\Users\myd7349\Desktop\CoilQueryTool\WPF\CoilQueryTool\CoilQueryTool\App.xaml.cs:line 22
   at System.Windows.Application.<.ctor>b__1_0(Object unused)
   at System.Windows.Threading.ExceptionWrapper.InternalRealCall(Delegate callback, Object args, Int32 numArgs)
   at System.Windows.Threading.ExceptionWrapper.TryCatchWhen(Object source, Delegate callback, Object args, Int32 numArgs, Delegate catchHandler)
   at System.Windows.Threading.DispatcherOperation.InvokeImpl()
   at System.Windows.Threading.DispatcherOperation.InvokeInSecurityContext(Object state)
   at MS.Internal.CulturePreservingExecutionContext.CallbackWrapper(Object obj)
   at System.Threading.ExecutionContext.RunInternal(ExecutionContext executionContext, ContextCallback callback, Object state)
--- End of stack trace from previous location ---
   at System.Threading.ExecutionContext.RunInternal(ExecutionContext executionContext, ContextCallback callback, Object state)
   at System.Threading.ExecutionContext.Run(ExecutionContext executionContext, ContextCallback callback, Object state)
   at MS.Internal.CulturePreservingExecutionContext.Run(CulturePreservingExecutionContext executionContext, ContextCallback callback, Object state)
   at System.Windows.Threading.DispatcherOperation.Invoke()
   at System.Windows.Threading.Dispatcher.ProcessQueue()
   at System.Windows.Threading.Dispatcher.WndProcHook(IntPtr hwnd, Int32 msg, IntPtr wParam, IntPtr lParam, Boolean& handled)
   at MS.Win32.HwndWrapper.WndProc(IntPtr hwnd, Int32 msg, IntPtr wParam, IntPtr lParam, Boolean& handled)
   at MS.Win32.HwndSubclass.DispatcherCallbackOperation(Object o)
   at System.Windows.Threading.ExceptionWrapper.InternalRealCall(Delegate callback, Object args, Int32 numArgs)
   at System.Windows.Threading.ExceptionWrapper.TryCatchWhen(Object source, Delegate callback, Object args, Int32 numArgs, Delegate catchHandler)
   at System.Windows.Threading.Dispatcher.LegacyInvokeImpl(DispatcherPriority priority, TimeSpan timeout, Delegate method, Object args, Int32 numArgs)
   at MS.Win32.HwndSubclass.SubclassWndProc(IntPtr hwnd, Int32 msg, IntPtr wParam, IntPtr lParam)
   at MS.Win32.UnsafeNativeMethods.DispatchMessage(MSG& msg)
   at System.Windows.Threading.Dispatcher.PushFrameImpl(DispatcherFrame frame)
   at System.Windows.Threading.Dispatcher.PushFrame(DispatcherFrame frame)
   at System.Windows.Threading.Dispatcher.Run()
   at System.Windows.Application.RunDispatcher(Object ignore)
   at System.Windows.Application.RunInternal(Window window)
   at System.Windows.Application.Run()
   at CoilQueryTool.App.Main()
*/

// [Why GetEntryAssembly returns null?](https://stackoverflow.com/questions/40217214/why-getentryassembly-returns-null)

/*
C:\Users\myd7349\Desktop\CoilQueryTool\WPF\CoilQueryTool\CoilQueryTool\Common\ConfigFileBase.cs(16,45): warning IL3000: 'Sys
tem.Reflection.Assembly.Location' always returns an empty string for assemblies embedded in a single-file app. If the p
ath to the app directory is needed, consider calling 'System.AppContext.BaseDirectory'. [C:\Users\myd7349\Desktop\CoilQueryT
ool\WPF\CoilQueryTool\CoilQueryTool\CoilQueryTool_xiwbtoio_wpftmp.csproj]
C:\Users\myd7349\Desktop\CoilQueryTool\WPF\CoilQueryTool\CoilQueryTool\Common\ConfigFileBase.cs(16,45): warning IL3000: 'Sys
tem.Reflection.Assembly.Location' always returns an empty string for assemblies embedded in a single-file app. If the p
ath to the app directory is needed, consider calling 'System.AppContext.BaseDirectory'. [C:\Users\myd7349\Desktop\CoilQueryT
ool\WPF\CoilQueryTool\CoilQueryTool\CoilQueryTool.csproj]
*/
