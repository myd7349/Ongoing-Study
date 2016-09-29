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

            Common.Util.Pause();
        }
    }
}

// References:
// [Get current folder path](http://stackoverflow.com/questions/15653921/get-current-folder-path)
// [mono c# get application path](http://stackoverflow.com/questions/6246074/mono-c-sharp-get-application-path/18562036#18562036)
