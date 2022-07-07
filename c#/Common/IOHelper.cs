// 2016-06-14T17:54+08:00
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

using Microsoft.VisualBasic.FileIO;

namespace Common.IO
{
    public static class IOHelper
    {
        public static string GetAppPath()
        {
            return Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
        }

        public static void AppendAllBytes(string path, byte[] bytes)
        {
            if (string.IsNullOrEmpty(path))
                throw new ArgumentException("path");

            if (bytes == null)
                throw new ArgumentNullException("bytes");

            using (var stream = new FileStream(path, FileMode.Append))
            {
                stream.Write(bytes, 0, bytes.Length);
            }
        }

        public static IEnumerable<string> EnumerateLines(string filePath, Encoding encoding = null, Predicate<string> predicate = null)
        {
            if (string.IsNullOrEmpty(filePath))
                throw new ArgumentException("filePath");

            using (var fileStream = File.OpenRead(filePath))
            using (var streamReader = encoding == null ? new StreamReader(fileStream) : new StreamReader(fileStream, encoding))
            {
                string line = null;

                if (predicate == null)
                {
                    while ((line = streamReader.ReadLine()) != null)
                        yield return line;
                }
                else
                {
                    while ((line = streamReader.ReadLine()) != null)
                    {
                        if (predicate(line))
                            yield return line;
                    }
                }
            }
        }

        public static bool LocateFileInExplorer(string filePath)
        {
            if (!File.Exists(filePath))
                return false;

            // Clean up file path so it can be navigated OK
            filePath = Path.GetFullPath(filePath);
            try
            {
                ProcessHelpers.StartProcessAsync("explorer.exe", string.Format("/select,\"{0}\"", filePath));
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                return false;
            }

            return true;
        }

        public static string AddLastDirectorySeparatorChar(string path)
        {
            if (string.IsNullOrEmpty(path))
                throw new ArgumentException(nameof(path));

            var lastChar = path[path.Length - 1];
            if (lastChar != Path.DirectorySeparatorChar &&
                lastChar != Path.AltDirectorySeparatorChar)
                path += Path.DirectorySeparatorChar;

            return path;
        }

        public static string RemoveLastDirectorySeparatorChar(string path)
        {
            if (string.IsNullOrEmpty(path))
                throw new ArgumentException(nameof(path));

            // TODO: Use TrimEnd
            var lastChar = path[path.Length - 1];
            if (lastChar == Path.DirectorySeparatorChar ||
                lastChar == Path.AltDirectorySeparatorChar)
                path = path.Substring(0, path.Length - 1);

            return path;
        }

        public static string MakeRelativePath(string relativeTo, string path, bool? withLastDirectorySeparatorChar = null)
        {
            if (string.IsNullOrEmpty(relativeTo))
                throw new ArgumentNullException(nameof(relativeTo));

            if (string.IsNullOrEmpty(path))
                throw new ArgumentNullException(nameof(path));

#if false
            var lastChar = relativeTo[relativeTo.Length - 1];
            if (lastChar != Path.DirectorySeparatorChar &&
                lastChar != Path.AltDirectorySeparatorChar)
                relativeTo += Path.DirectorySeparatorChar;
#else
            if (withLastDirectorySeparatorChar == true)
                relativeTo = AddLastDirectorySeparatorChar(relativeTo);
            else if (withLastDirectorySeparatorChar == false)
                relativeTo = RemoveLastDirectorySeparatorChar(relativeTo);
#endif

            var relativeToUri = new Uri(relativeTo);
            var pathUri = new Uri(path);

            if (relativeToUri.Scheme != pathUri.Scheme)
                return path; // path can't be made relative.

            var relativeUri = relativeToUri.MakeRelativeUri(pathUri);
            var relativePath = Uri.UnescapeDataString(relativeUri.ToString());

            if (pathUri.Scheme.Equals("file", StringComparison.InvariantCultureIgnoreCase))
                relativePath = relativePath.Replace(Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar);

            return relativePath;
        }

        public static IEnumerable<string> EnumerateFiles(string path, params string[] extensions)
        {
            return EnumerateFiles(path, System.IO.SearchOption.TopDirectoryOnly, extensions);
        }

        public static IEnumerable<string> EnumerateFiles(string path, System.IO.SearchOption searchOption, params string[] extensions)
        {
            if (extensions.Length == 0)
            {
                return Directory.EnumerateFiles(path, "*", searchOption);
            }
            else if (extensions.Length == 1)
            {
                var extension = extensions[0];
                if (extension.StartsWith("."))
                    extension = '*' + extension;
                return Directory.EnumerateFiles(path, extension, searchOption);
            }
            else
            {
                var extensionsSet = extensions.ToHashSet(StringComparer.OrdinalIgnoreCase);
                return Directory.EnumerateFiles(path, "*.*", searchOption)
                    .Where(filePath => extensionsSet.Contains(Path.GetExtension(filePath)));
            }
        }

        public static string GetBaseName(string path)
        {
            if (path == null)
                throw new ArgumentNullException(nameof(path));
        
            path = path.TrimEnd(Path.DirectorySeparatorChar)
                .TrimEnd(Path.AltDirectorySeparatorChar);
            return Path.GetFileName(path);
        }

        public static string GetBaseNameV2(string path)
        {
            if (path == null)
                throw new ArgumentNullException(nameof(path));
        
            return new DirectoryInfo(path).Name;
        }

        public static string GetTempFileName(string extension = null, string tempPath = null)
        {
            if (string.IsNullOrEmpty(extension))
                extension = ".tmp";

            if (string.IsNullOrEmpty(tempPath))
                tempPath = Path.GetTempPath();

            return Path.Combine(tempPath, Guid.NewGuid().ToString() + extension);
        }

        public static void OpenWithDefaultProgram(string path)
        {
            using (var process = new Process())
            {
                process.StartInfo.FileName = "explorer";
                process.StartInfo.Arguments = "\"" + path + "\"";
                process.Start();
            }
        }

        // Move file to recycle bin
        public static void DeleteFileToRecycleBin(string path)
        {
            if (File.Exists(path))
                FileSystem.DeleteFile(path, UIOption.OnlyErrorDialogs, RecycleOption.SendToRecycleBin);
        }

        public static void DeleteDirectoryToRecycleBin(string path)
        {
            if (Directory.Exists(path))
                FileSystem.DeleteDirectory(path, UIOption.OnlyErrorDialogs, RecycleOption.SendToRecycleBin);
        }
    }

    public static class PathUtils
    {
        // Microsoft.VisualBasic.FileIO.FileSystem.FileExists
        public static bool IsFile(string path)
        {
            // File.Exists(path) returns False if `path` is a directory.
            return File.Exists(path);
#if false
            try
            {
                var attr = File.GetAttributes(path);
                return !attr.HasFlag(FileAttributes.Directory);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e);
                return false;
            }
#endif
        }

        // Microsoft.VisualBasic.FileIO.FileSystem.DirectoryExists
        public static bool IsDirectory(string path)
        {
            // File.Exists(path) returns False if `path` is a directory.
            return Directory.Exists(path);
#if false
            try
            {
                var attr = File.GetAttributes(path);
                return attr.HasFlag(FileAttributes.Directory);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e);
                return false;
            }
#endif
        }

        public static bool IsAbsolute(string path)
        {
            return Path.IsPathRooted(path);
        }

        public static string GetRelativePath(string fullPath, string startPath)
        {
            var fullPathUri = new Uri(fullPath);
            var startPathUri = new Uri(startPath);

            return startPathUri.MakeRelativeUri(fullPathUri).ToString();
        }

        // [PathCanonicalize equivalent in C#](https://stackoverflow.com/questions/623333/pathcanonicalize-equivalent-in-c-sharp)
        // TODO: Fix for: NormalizePath("123.RPT");
        public static string NormalizePath(string path, bool? keepLastDirectorySeparator = null)
        {
            var fullPath = Path.GetFullPath(new Uri(path).LocalPath);

            if (keepLastDirectorySeparator == null)
                return fullPath;
            else if (keepLastDirectorySeparator == true)
                return IOHelper.AddLastDirectorySeparatorChar(fullPath);
            else
                return fullPath.TrimEnd(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar);
        }

        // IsSamePath(@"D:\123", @"D:/123");
        // IsSamePath(@"D:\123\", @"D:/123");
        // IsSamePath(@"D:\123\456\..\", @"D:/123");
        public static bool IsSamePath(string path1, string path2)
        {
            return string.Compare(NormalizePath(path1, false), NormalizePath(path2, false), true) == 0;
        }

        public static bool IsDirectoryEmpty(string path)
        {
            return !Directory.EnumerateFileSystemEntries(path).Any();
        }

        public static string QuotePath(string path, bool force = false)
        {
            if ((force || path.Contains(' ')) && !path.Contains('"'))
                return "\"" + path + "\"";
            else
                return path;
        }

        public static bool PathContainsInvalidChars(string path)
        {
            if (string.IsNullOrWhiteSpace(path))
                return false;

            return path.Any(ch => Path.GetInvalidPathChars().Contains(ch));
        }

        public static bool FileNameContainsInvalidChars(string fileName)
        {
            if (string.IsNullOrWhiteSpace(fileName))
                return false;

            return fileName.Any(ch => Path.GetInvalidFileNameChars().Contains(ch));
        }
    }

    public static class DirUtils
    {
        public static string[] ListDir(string path, bool silence = true)
        {
            try
            {
                return Directory.GetFileSystemEntries(path);
            }
            catch (Exception e) // DirectoryNotFoundException,SecurityException,ArgumentNullException
            {
                Debug.WriteLine(e);
                if (!silence)
                    throw;

                return new string[0];
            }
        }

        public static IEnumerable<string> Walk(string path, bool recursively = true, bool topdown = true, bool silence = true)
        {
            if (!PathUtils.IsAbsolute(path))
                path = Path.GetFullPath(path);

            IEnumerable<string> entries = recursively ? WalkRecursively(path, topdown, silence) : ListDir(path, silence);
            foreach (var entry in entries)
                yield return entry;
        }

        private delegate string FullPathDelegate(string entry);

        private static IEnumerable<string> WalkRecursively(string path, bool topdown, bool silence)
        {
            FullPathDelegate FullPath = entry => Path.GetFullPath(Path.Combine(path, entry));

            foreach (var entry in ListDir(path, silence))
            {
                var fullPath = FullPath(entry);

                if (topdown)
                    yield return fullPath;

                if (PathUtils.IsDirectory(fullPath))
                {
                    Debug.WriteLine("Directory: " + fullPath);
                    foreach (var subEntry in WalkRecursively(fullPath, topdown, silence))
                        yield return subEntry;
                }

                if (!topdown)
                    yield return fullPath;
            }
        }
    }
}

// References:
// [IEnumerable and Recursion using yield return](http://stackoverflow.com/questions/2055927/ienumerable-and-recursion-using-yield-return)
// [How to: Iterate Through a Directory Tree (C# Programming Guide)](https://msdn.microsoft.com/en-us/library/bb513869.aspx)
// [Walk a directory/Recursively](http://rosettacode.org/wiki/Walk_a_directory/Recursively#C.23)
// [Better way to check if Path is a File or a Directory?](http://stackoverflow.com/questions/1395205/better-way-to-check-if-path-is-a-file-or-a-directory)
// [Check if full path given](http://stackoverflow.com/questions/5565029/check-if-full-path-given)
// [How to Convert Absolute File Path To Relative Path in C#?](https://social.msdn.microsoft.com/Forums/zh-CN/954346c8-cbe8-448c-80d0-d3fc27796e9c/how-to-convert-absolute-file-path-to-relative-path-in-c?forum=csharpgeneral)
//
// C# 6.0 in a Nutshell, P654
//   IEnumerable<string> EnumerateFiles (string path);
//   IEnumerable<string> EnumerateDirectories (string path);
//   IEnumerable<string> EnumerateFileSystemEntries (string path);
// These three methods were added in Framework 4.0.
//
// [How can I compare (directory) paths in C#?](https://stackoverflow.com/questions/2281531/how-can-i-compare-directory-paths-in-c)
// [How to quickly check if folder is empty (.NET)?](https://stackoverflow.com/questions/755574/how-to-quickly-check-if-folder-is-empty-net)
// [In C# check that filename is *possibly* valid (not that it exists)](https://stackoverflow.com/questions/422090/in-c-sharp-check-that-filename-is-possibly-valid-not-that-it-exists)
// [How do I check if a given string is a legal/valid file name under Windows?](https://stackoverflow.com/questions/62771/how-do-i-check-if-a-given-string-is-a-legal-valid-file-name-under-windows)
// [C# Append byte array to existing file](https://stackoverflow.com/questions/6862368/c-sharp-append-byte-array-to-existing-file)
// [How to read a text file one line at a time (C# Programming Guide)](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/file-system/how-to-read-a-text-file-one-line-at-a-time)
// https://github.com/microsoft/perfview/blob/main/src/Utilities/FileUtilities.cs
// https://github.com/microsoft/perfview/blob/main/src/Utilities/DirectoryUtilities.cs
// https://github.com/microsoft/perfview/blob/main/src/Utilities/StreamUtilities.cs
// https://github.com/microsoft/accessibility-insights-windows/blob/main/src/AccessibilityInsights.SetupLibrary/FileHelpers.cs
// [How to open Explorer with a specific file selected?](https://stackoverflow.com/questions/13680415/how-to-open-explorer-with-a-specific-file-selected)
// [https://stackoverflow.com/questions/3400884/how-do-i-open-an-explorer-window-in-a-given-directory-from-cmd-exe](https://stackoverflow.com/questions/3400884/how-do-i-open-an-explorer-window-in-a-given-directory-from-cmd-exe)
// [How to get relative path from absolute path](https://stackoverflow.com/questions/275689/how-to-get-relative-path-from-absolute-path)
// [Path.GetRelativePath(String, String)](https://learn.microsoft.com/en-us/dotnet/api/system.io.path.getrelativepath)
// [Can you call Directory.GetFiles() with multiple filters?](https://stackoverflow.com/questions/163162/can-you-call-directory-getfiles-with-multiple-filters)
// [How can I create a temp file with a specific extension with .NET?](https://stackoverflow.com/questions/581570/how-can-i-create-a-temp-file-with-a-specific-extension-with-net)
// [c# open file with default application and parameters](https://stackoverflow.com/questions/11365984/c-sharp-open-file-with-default-application-and-parameters)
// [Get the (last part of) current directory name in C#](https://stackoverflow.com/questions/6018293/get-the-last-part-of-current-directory-name-in-c-sharp)
// https://en.wikipedia.org/wiki/Basename
// [Verifying path equality with .Net](https://stackoverflow.com/questions/7344978/verifying-path-equality-with-net)
// [Best way to determine if two path reference to same file in C#](https://stackoverflow.com/questions/410705/best-way-to-determine-if-two-path-reference-to-same-file-in-c-sharp)
// [Detect if two paths are the same](https://stackoverflow.com/questions/31097236/detect-if-two-paths-are-the-same)
// > Path.GetRandomFileName
// [How to determine if two directory pathnames resolve to the same target](https://superuser.com/questions/881547/how-to-determine-if-two-directory-pathnames-resolve-to-the-same-target)
// [PathCanonicalize equivalent in C#](https://stackoverflow.com/questions/623333/pathcanonicalize-equivalent-in-c-sharp)
// [C# Remove all empty subdirectories](https://stackoverflow.com/questions/2811509/c-sharp-remove-all-empty-subdirectories)
// [Send a File to the Recycle Bin](https://stackoverflow.com/questions/3282418/send-a-file-to-the-recycle-bin)
