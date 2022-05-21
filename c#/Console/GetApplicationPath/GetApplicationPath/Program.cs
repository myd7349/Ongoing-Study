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

