namespace Common
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Runtime.InteropServices;
    using System.Threading.Tasks;

    public static class ProcessHelpers
    {
        public static IEnumerable<Process> FindProcesses(Predicate<Process> predicate)
        {
            if (predicate == null)
                throw new ArgumentNullException("predicate");

            var processes = Process.GetProcesses();
            for (int i = 0; i < processes.Length; ++i)
            {
                if (predicate(processes[i]))
                    yield return processes[i];
            }
        }

        public static Process FindProcess(Predicate<Process> predicate)
        {
            return FindProcesses(predicate).FirstOrDefault();
        }

        public static Process GetSameProcess(Process process = null)
        {
            if (process == null)
                process = Process.GetCurrentProcess();

            return FindProcess(
                p =>
                {
                    try
                    {
                        return p.Id != process.Id &&
                            IO.PathUtils.IsSamePath(p.MainModule.FileName, process.MainModule.FileName);
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine("{0}", ex);
                        return false;
                    }
                });
        }

        public static bool IsProcessStarted(Process process = null)
        {
            return GetSameProcess(process) != null;
        }

        public static void BringProcessToFront(Process process)
        {
            IntPtr handle = process.MainWindowHandle;
            if (handle == IntPtr.Zero)
                return;
                
            if (IsIconic(handle))
            {
                ShowWindow(handle, SW_RESTORE);
            }

            SetForegroundWindow(handle);
        }

        public static Task<int> StartProcessAsync(string fileName, string arguments)
        {
            var tcs = new TaskCompletionSource<int>();

            var process = new Process
            {
                StartInfo =
                {
                    FileName = fileName,
                    Arguments = arguments,
                },
                EnableRaisingEvents = true
            };

            process.Exited += (sender, args) =>
            {
                tcs.SetResult(process.ExitCode);
                process.Dispose();
            };

            process.Start();

            return tcs.Task;
        }

        const int SW_RESTORE = 9;

        [DllImport("User32.dll")]
        private static extern bool SetForegroundWindow(IntPtr handle);

        [DllImport("User32.dll")]
        private static extern bool ShowWindow(IntPtr handle, int nCmdShow);

        [DllImport("User32.dll")]
        private static extern bool IsIconic(IntPtr handle);
    }
}


// References:
// https://stackoverflow.com/questions/2636721/bring-another-processes-window-to-foreground-when-it-has-showintaskbar-false
// https://github.com/microsoft/perfview/blob/main/src/HeapDump/GCHeapDump.cs
// [Restore application from system tray when clicking on desktop shortcut](https://stackoverflow.com/questions/10529370/restore-application-from-system-tray-when-clicking-on-desktop-shortcut)
// [Is there any async equivalent of Process.Start?](https://stackoverflow.com/questions/10788982/is-there-any-async-equivalent-of-process-start)
// https://github.com/PixiEditor/PixiEditor/blob/master/src/PixiEditor/Helpers/ProcessHelper.cs
