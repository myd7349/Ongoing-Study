namespace Common
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Runtime.InteropServices;

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

        public static bool IsProcessStarted(Process process)
        {
            if (process == null)
                throw new ArgumentNullException("process");

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
