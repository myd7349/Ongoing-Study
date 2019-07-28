// How?
// 0. Decompile System.Data.SQLite.dll with ILSpy
//    and save the decompiled result with:
//    File -> Save Code...
// 1. Suppose the decompiled code is saved to:
//    ./sqlite
//    then:
//    > cd ./sqlite
//    > git init
//    > git add -A
//    > git commit -m whatever
//    > git grep DllImport
//    > git grep x64
namespace Native.Interop
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Globalization;
    using System.IO;
    using System.Reflection;
    using System.Runtime.InteropServices;
    using System.Runtime.Versioning;
    using System.Xml;

    public static class UnsafeNativeMethods
    {
        static UnsafeNativeMethods()
        {
            DllFileExtension = ".dll";
            ConfigFileExtension = ".config";
            XmlConfigFileName = typeof(UnsafeNativeMethods).Namespace + DllFileExtension + ConfigFileExtension;
            XmlConfigDirectoryToken = "%PreLoadSQLite_XmlConfigDirectory%";
            AssemblyDirectoryToken = "%PreLoadSQLite_AssemblyDirectory%";
            TargetFrameworkToken = "%PreLoadSQLite_TargetFramework%";
            staticSyncRoot = new object();
            PROCESSOR_ARCHITECTURE = "PROCESSOR_ARCHITECTURE";
            _SQLiteNativeModuleFileName = null;
            _SQLiteNativeModuleHandle = IntPtr.Zero;
            Initialize();
        }

        [DllImport("NativeLib.dll")]
        public static extern void Foo();

        internal static void Initialize()
        {
            lock (staticSyncRoot)
            {
                if (processorArchitecturePlatforms == null)
                {
                    processorArchitecturePlatforms = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
                    processorArchitecturePlatforms.Add("x86", "Win32");
                    processorArchitecturePlatforms.Add("AMD64", "x64");
                    processorArchitecturePlatforms.Add("IA64", "Itanium");
                    processorArchitecturePlatforms.Add("ARM", "WinCE");
                }
                if (_SQLiteNativeModuleHandle == IntPtr.Zero)
                {
                    string baseDirectory = null;
                    string processorArchitecture = null;
                    SearchForDirectory(ref baseDirectory, ref processorArchitecture);
                    PreLoadSQLiteDll(baseDirectory, processorArchitecture, ref _SQLiteNativeModuleFileName, ref _SQLiteNativeModuleHandle);
                }
            }
        }

        private static string GetBaseDirectory()
        {
            string settingValue = GetSettingValue("PreLoadSQLite_BaseDirectory", null);
            if (settingValue != null)
            {
                return settingValue;
            }
            if (GetSettingValue("PreLoadSQLite_UseAssemblyDirectory", null) != null)
            {
                settingValue = GetAssemblyDirectory();
                if (settingValue != null)
                {
                    return settingValue;
                }
            }
            return AppDomain.CurrentDomain.BaseDirectory;
        }

        private static bool PreLoadSQLiteDll(string baseDirectory, string processorArchitecture, ref string nativeModuleFileName, ref IntPtr nativeModuleHandle)
        {
            if (baseDirectory == null)
            {
                baseDirectory = GetBaseDirectory();
            }
            if (baseDirectory == null)
            {
                return false;
            }
            string nativeLibraryFileNameOnly = GetNativeLibraryFileNameOnly();
            if (nativeLibraryFileNameOnly == null)
            {
                return false;
            }
            string path = FixUpDllFileName(MaybeCombinePath(baseDirectory, nativeLibraryFileNameOnly));
            if (File.Exists(path))
            {
                return false;
            }
            if (processorArchitecture == null)
            {
                processorArchitecture = GetProcessorArchitecture();
            }
            if (processorArchitecture == null)
            {
                return false;
            }
            path = FixUpDllFileName(MaybeCombinePath(MaybeCombinePath(baseDirectory, processorArchitecture), nativeLibraryFileNameOnly));
            if (!File.Exists(path))
            {
                string platformName = GetPlatformName(processorArchitecture);
                if (platformName == null)
                {
                    return false;
                }
                path = FixUpDllFileName(MaybeCombinePath(MaybeCombinePath(baseDirectory, platformName), nativeLibraryFileNameOnly));
                if (!File.Exists(path))
                {
                    return false;
                }
            }
            try
            {
                try
                {
                    Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader is trying to load native SQLite library \"{0}\"...", path));
                }
                catch
                {
                }
                nativeModuleFileName = path;
                nativeModuleHandle = NativeLibraryHelper.LoadLibrary(path);
                return nativeModuleHandle != IntPtr.Zero;
            }
            catch (Exception ex)
            {
                try
                {
                    int lastWin32Error = Marshal.GetLastWin32Error();
                    Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to load native SQLite library \"{0}\" (getLastError = {1}): {2}", path, lastWin32Error, ex));
                }
                catch
                {
                }
            }
            return false;
        }

        internal static string GetNativeLibraryFileNameOnly()
        {
            string settingValue = GetSettingValue("PreLoadSQLite_LibraryFileNameOnly", null);
            if (settingValue != null)
            {
                return settingValue;
            }
            return "SQLite.Interop.dll";
        }

        private static bool SearchForDirectory(ref string baseDirectory, ref string processorArchitecture)
        {
            if (GetSettingValue("PreLoadSQLite_NoSearchForDirectory", null) != null)
            {
                return false;
            }
            string nativeLibraryFileNameOnly = GetNativeLibraryFileNameOnly();
            if (nativeLibraryFileNameOnly == null)
            {
                return false;
            }
            string[] array = new string[2]
            {
                GetAssemblyDirectory(),
                AppDomain.CurrentDomain.BaseDirectory
            };
            string[] array2 = new string[2]
            {
                GetProcessorArchitecture(),
                GetPlatformName(null)
            };
            string[] array3 = array;
            foreach (string text in array3)
            {
                if (text != null)
                {
                    string[] array4 = array2;
                    foreach (string text2 in array4)
                    {
                        if (text2 != null)
                        {
                            string path = FixUpDllFileName(MaybeCombinePath(MaybeCombinePath(text, text2), nativeLibraryFileNameOnly));
                            if (File.Exists(path))
                            {
                                baseDirectory = text;
                                processorArchitecture = text2;
                                return true;
                            }
                        }
                    }
                }
            }

            return false;
        }

        private static string GetPlatformName(string processorArchitecture)
        {
            if (processorArchitecture == null)
            {
                processorArchitecture = GetProcessorArchitecture();
            }
            if (string.IsNullOrEmpty(processorArchitecture))
            {
                return null;
            }
            lock (staticSyncRoot)
            {
                if (processorArchitecturePlatforms == null)
                {
                    return null;
                }
                string result = default(string);
                if (processorArchitecturePlatforms.TryGetValue(processorArchitecture, out result))
                {
                    return result;
                }
            }
            return null;
        }

        private static string GetProcessorArchitecture()
        {
            string settingValue = GetSettingValue("PreLoadSQLite_ProcessorArchitecture", null);
            if (settingValue != null)
            {
                return settingValue;
            }
            settingValue = GetSettingValue(PROCESSOR_ARCHITECTURE, null);
            if (IntPtr.Size == 4 && string.Equals(settingValue, "AMD64", StringComparison.OrdinalIgnoreCase))
            {
                settingValue = "x86";
            }
            return settingValue;
        }

        private static string GetSettingValueViaXmlConfigFile(string fileName, string name, string @default, bool expand)
        {
            try
            {
                if (fileName != null && name != null)
                {
                    XmlDocument xmlDocument = new XmlDocument();
                    xmlDocument.Load(fileName);
                    XmlElement xmlElement = xmlDocument.SelectSingleNode(HelperMethods.StringFormat(CultureInfo.InvariantCulture, "/configuration/appSettings/add[@key='{0}']", name)) as XmlElement;
                    if (xmlElement != null)
                    {
                        string text = null;
                        if (xmlElement.HasAttribute("value"))
                        {
                            text = xmlElement.GetAttribute("value");
                        }
                        if (!string.IsNullOrEmpty(text))
                        {
                            if (expand)
                            {
                                text = Environment.ExpandEnvironmentVariables(text);
                            }
                            text = ReplaceEnvironmentVariableTokens(text);
                            text = ReplaceXmlConfigFileTokens(fileName, text);
                        }
                        if (text != null)
                        {
                            return text;
                        }
                        return @default;
                    }
                    return @default;
                }
                return @default;
            }
            catch (Exception ex)
            {
                try
                {
                    Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to get setting \"{0}\" value from XML configuration file \"{1}\": {2}", name, fileName, ex));
                    return @default;
                }
                catch
                {
                    return @default;
                }
            }
        }

        private static string ReplaceEnvironmentVariableTokens(string value)
        {
            if (!string.IsNullOrEmpty(value))
            {
                string text = GetCachedAssemblyDirectory();
                if (!string.IsNullOrEmpty(text))
                {
                    try
                    {
                        value = value.Replace(AssemblyDirectoryToken, text);
                    }
                    catch (Exception ex)
                    {
                        try
                        {
                            Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to replace assembly directory token: {0}", ex));
                        }
                        catch
                        {
                        }
                    }
                }
                Assembly assembly = null;
                try
                {
                    assembly = Assembly.GetExecutingAssembly();
                }
                catch (Exception ex2)
                {
                    try
                    {
                        Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to obtain executing assembly: {0}", ex2));
                    }
                    catch
                    {
                    }
                }
                string text2 = AbbreviateTargetFramework(GetAssemblyTargetFramework(assembly));
                if (!string.IsNullOrEmpty(text2))
                {
                    try
                    {
                        value = value.Replace(TargetFrameworkToken, text2);
                        return value;
                    }
                    catch (Exception ex3)
                    {
                        try
                        {
                            Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to replace target framework token: {0}", ex3));
                            return value;
                        }
                        catch
                        {
                            return value;
                        }
                    }
                }
            }
            return value;
        }

        private static string GetCachedAssemblyDirectory()
        {
            lock (staticSyncRoot)
            {
                if (cachedAssemblyDirectory != null)
                {
                    return cachedAssemblyDirectory;
                }
                if (noAssemblyDirectory)
                {
                    return null;
                }
            }
            return GetAssemblyDirectory();
        }

        private static string GetAssemblyDirectory()
        {
            try
            {
                Assembly executingAssembly = Assembly.GetExecutingAssembly();
                if (executingAssembly == null)
                {
                    lock (staticSyncRoot)
                    {
                        noAssemblyDirectory = true;
                    }
                    return null;
                }
                string text = null;
                if (!CheckAssemblyCodeBase(executingAssembly, ref text))
                {
                    text = executingAssembly.Location;
                }
                if (string.IsNullOrEmpty(text))
                {
                    lock (staticSyncRoot)
                    {
                        noAssemblyDirectory = true;
                    }
                    return null;
                }
                string directoryName = Path.GetDirectoryName(text);
                if (string.IsNullOrEmpty(directoryName))
                {
                    lock (staticSyncRoot)
                    {
                        noAssemblyDirectory = true;
                    }
                    return null;
                }
                lock (staticSyncRoot)
                {
                    cachedAssemblyDirectory = directoryName;
                }
                return directoryName;
            }
            catch (Exception ex)
            {
                try
                {
                    Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to get directory for currently executing assembly: {0}", ex));
                }
                catch
                {
                }
            }
            lock (staticSyncRoot)
            {
                noAssemblyDirectory = true;
            }
            return null;
        }

        private static bool CheckAssemblyCodeBase(Assembly assembly, ref string fileName)
        {
            try
            {
                if (assembly == null)
                {
                    return false;
                }
                string codeBase = assembly.CodeBase;
                if (string.IsNullOrEmpty(codeBase))
                {
                    return false;
                }
                Uri uri = new Uri(codeBase);
                string localPath = uri.LocalPath;
                if (!File.Exists(localPath))
                {
                    return false;
                }
                string directoryName = Path.GetDirectoryName(localPath);
                string path = MaybeCombinePath(directoryName, XmlConfigFileName);
                if (File.Exists(path))
                {
                    fileName = localPath;
                    return true;
                }
                List<string> list = null;
                if (CheckForArchitecturesAndPlatforms(directoryName, ref list) > 0)
                {
                    fileName = localPath;
                    return true;
                }
                return false;
            }
            catch (Exception ex)
            {
                try
                {
                    Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to check code base for currently executing assembly: {0}", ex));
                }
                catch
                {
                }
            }
            return false;
        }

        private static string MaybeCombinePath(string path1, string path2)
        {
            if (path1 != null)
            {
                if (path2 != null)
                {
                    return Path.Combine(path1, path2);
                }
                return path1;
            }
            if (path2 != null)
            {
                return path2;
            }
            return null;
        }

        private static int CheckForArchitecturesAndPlatforms(string directory, ref List<string> matches)
        {
            int num = 0;
            if (matches == null)
            {
                matches = new List<string>();
            }
            lock (staticSyncRoot)
            {
                if (!string.IsNullOrEmpty(directory))
                {
                    if (processorArchitecturePlatforms != null)
                    {
                        {
                            foreach (KeyValuePair<string, string> processorArchitecturePlatform in processorArchitecturePlatforms)
                            {
                                if (Directory.Exists(MaybeCombinePath(directory, processorArchitecturePlatform.Key)))
                                {
                                    matches.Add(processorArchitecturePlatform.Key);
                                    num++;
                                }
                                string value = processorArchitecturePlatform.Value;
                                if (value != null && Directory.Exists(MaybeCombinePath(directory, value)))
                                {
                                    matches.Add(value);
                                    num++;
                                }
                            }
                            return num;
                        }
                    }
                    return num;
                }
                return num;
            }
        }

        private static string AbbreviateTargetFramework(string value)
        {
            if (string.IsNullOrEmpty(value))
            {
                return value;
            }
            value = value.Replace(".NETFramework,Version=v", "net");
            value = value.Replace(".", string.Empty);
            int num = value.IndexOf(',');
            if (num != -1)
            {
                value = value.Substring(0, num);
            }
            return value;
        }

        private static string GetAssemblyTargetFramework(Assembly assembly)
        {
            if (assembly != null)
            {
                try
                {
                    if (assembly.IsDefined(typeof(TargetFrameworkAttribute), false))
                    {
                        TargetFrameworkAttribute targetFrameworkAttribute = (TargetFrameworkAttribute)assembly.GetCustomAttributes(typeof(TargetFrameworkAttribute), false)[0];
                        return targetFrameworkAttribute.FrameworkName;
                    }
                }
                catch
                {
                }
            }
            return null;
        }

        private static string ReplaceXmlConfigFileTokens(string fileName, string value)
        {
            if (!string.IsNullOrEmpty(value) && !string.IsNullOrEmpty(fileName))
            {
                try
                {
                    string directoryName = Path.GetDirectoryName(fileName);
                    if (!string.IsNullOrEmpty(directoryName))
                    {
                        value = value.Replace(XmlConfigDirectoryToken, directoryName);
                        return value;
                    }
                    return value;
                }
                catch (Exception ex)
                {
                    try
                    {
                        Trace.WriteLine(HelperMethods.StringFormat(CultureInfo.CurrentCulture, "Native library pre-loader failed to replace XML configuration file \"{0}\" tokens: {1}", fileName, ex));
                        return value;
                    }
                    catch
                    {
                        return value;
                    }
                }
            }
            return value;
        }

        private static string FixUpDllFileName(string fileName)
        {
            if (!string.IsNullOrEmpty(fileName) && HelperMethods.IsWindows() && !fileName.EndsWith(DllFileExtension, StringComparison.OrdinalIgnoreCase))
            {
                return fileName + DllFileExtension;
            }
            return fileName;
        }
        
        internal static string GetSettingValue(string name, string @default)
        {
            if (Environment.GetEnvironmentVariable("No_SQLiteGetSettingValue") != null)
            {
                return @default;
            }
            if (name == null)
            {
                return @default;
            }
            bool flag = true;
            string text = null;
            if (Environment.GetEnvironmentVariable("No_Expand") != null)
            {
                flag = false;
            }
            else if (Environment.GetEnvironmentVariable(HelperMethods.StringFormat(CultureInfo.InvariantCulture, "No_Expand_{0}", name)) != null)
            {
                flag = false;
            }
            text = Environment.GetEnvironmentVariable(name);
            if (!string.IsNullOrEmpty(text))
            {
                if (flag)
                {
                    text = Environment.ExpandEnvironmentVariables(text);
                }
                text = ReplaceEnvironmentVariableTokens(text);
            }
            if (text != null)
            {
                return text;
            }
            if (Environment.GetEnvironmentVariable("No_SQLiteXmlConfigFile") != null)
            {
                return @default;
            }
            return GetSettingValueViaXmlConfigFile(GetCachedXmlConfigFileName(), name, @default, flag);
        }

        private static string GetCachedXmlConfigFileName()
        {
            lock (staticSyncRoot)
            {
                if (cachedXmlConfigFileName != null)
                {
                    return cachedXmlConfigFileName;
                }
                if (noXmlConfigFileName)
                {
                    return null;
                }
            }
            return GetXmlConfigFileName();
        }

        private static string GetXmlConfigFileName()
        {
            string baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
            string text = MaybeCombinePath(baseDirectory, XmlConfigFileName);
            if (File.Exists(text))
            {
                lock (staticSyncRoot)
                {
                    cachedXmlConfigFileName = text;
                    return text;
                }
            }
            baseDirectory = GetCachedAssemblyDirectory();
            text = MaybeCombinePath(baseDirectory, XmlConfigFileName);
            if (File.Exists(text))
            {
                lock (staticSyncRoot)
                {
                    cachedXmlConfigFileName = text;
                    return text;
                }
            }
            lock (staticSyncRoot)
            {
                noXmlConfigFileName = true;
            }
            return null;
        }

        private static readonly object staticSyncRoot;
        private static Dictionary<string, string> processorArchitecturePlatforms;
        private static IntPtr _SQLiteNativeModuleHandle;
        private static string cachedAssemblyDirectory;
        private static bool noAssemblyDirectory;
        private static readonly string XmlConfigFileName;
        private static readonly string DllFileExtension;
        private static readonly string ConfigFileExtension;
        private static readonly string AssemblyDirectoryToken;
        private static readonly string TargetFrameworkToken;
        private static readonly string XmlConfigDirectoryToken;
        private static readonly string PROCESSOR_ARCHITECTURE;
        private static string cachedXmlConfigFileName;
        private static bool noXmlConfigFileName;
        internal static string _SQLiteNativeModuleFileName;
    }
}


// References:
// System.Data.SQLite.UnsafeNativeMethods
