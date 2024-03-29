namespace Common
{
    using System;
    using System.Linq;

    using Microsoft.Win32;

    using Configuration.Registry;

    public static class AutoRunHelper
    {
        public static Tuple<string, string>[] GetAutoRunApplications()
        {
            using (var autoRunSubKey = Registry.CurrentUser.OpenSubKey(AutoRunSubKey))
            {
                return autoRunSubKey.EnumerateValues()
                    .Select(v => Tuple.Create(v.Item2, v.Item3?.ToString()))
                    .ToArray();
            }
        }

        private const string AutoRunSubKey = @"SOFTWARE\Microsoft\Windows\CurrentVersion\Run";
    }
}


// References:
// https://github.com/flameshot-org/flameshot/blob/ce336a6a70725ba47db54092026caab8c1f84c52/src/utils/confighandler.cpp#L230-L312
// https://github.com/Kyome22/RunCat_for_windows/blob/18da85c2e48dcf730d6e81156ca6ce6366990eb6/RunCat/Program.cs#L238-L254
// https://github.com/kfstorm/BingWallpaper/blob/ea5db46ce85acc6ef66fa3a25a853769720860f1/BingWallpaper/Program.cs#L102-L122
// https://github.com/Blinue/Magpie/blob/main/Magpie/Options/ApplicationOptionsPage.xaml.cs
// https://github.com/ChangemakerStudios/Papercut-SMTP
// https://github.com/Tyrrrz/LightBulb/blob/master/LightBulb/Services/SettingsService.cs
// https://github.com/cuiliang/Caps2CtrlSpace
// https://github.com/cuiliang/ClickShow
// https://github.com/Uahh/ToastFish
// https://github.com/Snipaste/feedback/issues/188
// > Login to admin account and add Snipaste.exe to startup using Nirsoft.net (free) "WhatInStartup" http://www.nirsoft.net/utils/what_run_in_startup.html ...
// > You can add items with "WhatInStartup"
// https://www.nirsoft.net/utils/what_run_in_startup.html
// https://github.com/LibreHardwareMonitor/LibreHardwareMonitor/blob/master/LibreHardwareMonitor/UI/StartupManager.cs
