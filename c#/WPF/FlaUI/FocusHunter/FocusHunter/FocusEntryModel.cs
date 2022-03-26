namespace FocusHunter
{
    using System;
    using System.Diagnostics;

    using FlaUI.Core.AutomationElements;

    public class FocusEntryModel
    {
        public FocusEntryModel(AutomationElement automationElement)
        {
            ProcessId = -1;
            Path = string.Empty;
            try
            {
                ProcessId = automationElement.Properties.ProcessId;
                var process = Process.GetProcessById(ProcessId);
                Path = process.MainModule.FileName;
            }
            catch (Exception ex)
            {
                Path = ex.ToString();
            }
        }

        public int ProcessId { get; private set; }

        public string Path { get; private set; }
    }
}


// References:
// [C#根据PID获取进程名](https://blog.sdlsj.net/archives/c-sharp/get-process-name-by-pid/)
