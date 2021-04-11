namespace MarshalCppClass
{
    using System;
    using System.IO;
    using System.Reflection;

    abstract class NativeDLLImporter : IDisposable
    {
        public const string DLLFileName = "NativeClassLib.dll";
        public static readonly NativeDLLImporter Instance;

        static NativeDLLImporter()
        {
            switch (Environment.OSVersion.Platform)
            {
                case PlatformID.Win32NT:
                case PlatformID.Win32S:
                case PlatformID.Win32Windows:
                case PlatformID.WinCE:
                    Instance = new WinNTDLLImporter();
                    break;
                case PlatformID.Xbox:
                case PlatformID.MacOSX:
                case PlatformID.Unix:
                    {
                        var message = string.Format(
                            "NativeDLLImporter is not implemented on {0}.",
                            Environment.OSVersion.Platform);
                        throw new NotImplementedException(message);
                    }
                default:
                    {
                        var message = string.Format(
                            "Unexpected platform {0}.",
                            Environment.OSVersion.Platform);
                        throw new NotImplementedException();
                    }
            }
        }

        public NativeDLLImporter()
        {
            string dllPath = null;

            var searchDir = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            if (IntPtr.Size == 8)
            {
                var x64DllPath = Path.Combine(searchDir, "x64", DLLFileName);
                if (File.Exists(x64DllPath))
                    dllPath = x64DllPath;
            }
            else
            {
                var x86DllPath = Path.Combine(searchDir, "x86", DLLFileName);
                if (File.Exists(x86DllPath))
                    dllPath = x86DllPath;
            }

            if (dllPath == null)
                dllPath = Path.Combine(searchDir, DLLFileName);

            LoadLibrary(dllPath);
        }

        // NOTE: Leave out the finalizer altogether if this class doesn't
        // own unmanaged resources, but leave the other methods
        // exactly as they are.
        ~NativeDLLImporter()
        {
            // Finalizer calls Dispose(false)
            Dispose(false);
        }

        public abstract void LoadLibrary(string path);

        public abstract void FreeLibrary();

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (disposed_)
                return;

            if (disposing)
            {
                // Free managed resources
                // ...
            }

            // Free native resources if there are any.
            FreeLibrary();

            disposed_ = true;
        }

        private bool disposed_ = false;
    }
}


// References:
// System.Data.SQLite.UnsafeNativeMethods
// https://github.com/HDFGroup/HDF.PInvoke/blob/master/HDF5/H5DLLImporter.cs
// https://github.com/HDFGroup/HDF.PInvoke/blob/d281aa75f1562e677d1307cc1a234f9079cd76c3/HDF5/NativeDependencies.cs
// [PInvoke.Kernel32](https://www.nuget.org/packages/PInvoke.Kernel32/)
// [dotnet/pinvoke](https://github.com/dotnet/pinvoke)
// [CA1063: Implement IDisposable correctly](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1063)
