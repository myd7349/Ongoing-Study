// 2016-06-14T18:55+08:00
using System;
using System.IO;
using System.Linq;

using Microsoft.VisualBasic.FileIO;

using Common;
using Common.IO;


namespace DirWalkerTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var dir = @"..\..\";
            Func<string, string> toRelativePath = path => PathUtils.GetRelativePath(path, Path.GetFullPath(dir));

            foreach (var entry in DirUtils.Walk(dir, true, false).Select(toRelativePath))
                Console.WriteLine(entry);

            Console.WriteLine("-------------------- Using Directory.EnumerateFileSystemEntries --------------------");
            foreach (var entry in Directory.EnumerateFileSystemEntries(dir, "*.*", System.IO.SearchOption.AllDirectories))
                Console.WriteLine(entry);

            // All sub-directories
            Console.WriteLine("-------------------- Sub-directories --------------------");
            foreach (var entry in DirUtils.Walk(dir, true, false).Where(PathUtils.IsDirectory))
                Console.WriteLine(entry);

            // All sub-directories
            Console.WriteLine("---------------- Sub-directories(ListDir) ----------------");
            foreach (var entry in FileSystem.GetDirectories(dir))
                Console.WriteLine(entry);

            // All sub-directories
            Console.WriteLine("---------------- Sub-directories(Recursively) ----------------");
            foreach (var entry in FileSystem.GetDirectories(dir, Microsoft.VisualBasic.FileIO.SearchOption.SearchAllSubDirectories))
                Console.WriteLine(entry);

            // All C# source code files
            Console.WriteLine("-------------------- C# source code files --------------------");
            Func<string, bool> isCSharpSourceCodeFile = path => PathUtils.IsFile(path) && path.EndsWith(".cs");
            foreach (var entry in DirUtils.Walk(dir, true, false)
                .Where(isCSharpSourceCodeFile)
                //.Select(toRelativePath)
                )
                Console.WriteLine(entry);

            Console.WriteLine("-------------------- C# source code files --------------------");
            Console.WriteLine("--------------- (Using Directory.EnumerateFiles) -------------");
            foreach (var entry in Directory.EnumerateFiles(dir, "*.cs", System.IO.SearchOption.AllDirectories))
                Console.WriteLine(entry);

            Console.WriteLine("-------------------- C# source code files --------------------");
            Console.WriteLine("--------------- (Using Microsoft.VisualBasic.FileIO.FileSystem.GetFiles) -------------");
            foreach (var entry in FileSystem.GetFiles(dir, Microsoft.VisualBasic.FileIO.SearchOption.SearchAllSubDirectories, "*.cs"))
                Console.WriteLine(entry);

            // List drives
            Console.WriteLine("-------------------- Drives --------------------");
            foreach (var drive in FileSystem.Drives)
                Console.WriteLine(drive);

            Util.Pause();
        }
    }
}

// References:
// C# 6.0 in a Nutshell, P654