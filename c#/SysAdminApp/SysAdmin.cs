// 2016-01-30T15:09+08:00
// By myd

using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Win32;

namespace SysAdminApp
{
    public sealed class SysAdmin
    {
        private static readonly string key;
        private static readonly string explorerSubKey;
        private static readonly string systemSubKey;

        private static readonly Dictionary<string, Int32> noDrivesDict;

        static SysAdmin()
        {
            key = @"HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies";
            explorerSubKey = key + @"\Explorer";
            systemSubKey = key + @"\System";

            Int32 mask = 1;
            noDrivesDict = new Dictionary<string, Int32>();

            for (char name = 'A'; name <= 'Z'; name++)
            {
                noDrivesDict[name+@":\"] = mask;
                mask <<= 1;
            }
 
            noDrivesDict["All"] = 0x03FFFFFF;
        }

        public static bool IsWinVistaOrHigher()
        {
            OperatingSystem os = Environment.OSVersion;
            return os.Platform == PlatformID.Win32NT && os.Version.Major >= 6; 
        }

        public static SortedDictionary<string, bool> GetDriveVisibilityDict()
        {
            Int32 noDrivesValue = GetInt32Value(explorerSubKey, "NoDrives", 0);

            var dict = new SortedDictionary<string, bool>();
            foreach (var driveInfo in System.IO.DriveInfo.GetDrives())
            {
                string driveName = driveInfo.Name;
                dict[driveName] = !noDrivesDict.ContainsKey(driveName)
                    || (noDrivesValue & noDrivesDict[driveName]) == 0;
            }

            return dict;
        }

        public static void SetDriveVisibility(SortedDictionary<string, bool> driveVisibilityDict)
        {
            Registry.SetValue(explorerSubKey, "NoDrives", 
                GetNoDrivesValue(driveVisibilityDict), RegistryValueKind.DWord);
        }

        public static void SetNoDispCPL(bool noDispCPL)
        {
            OpenOption(systemSubKey, "NoDispCPL", noDispCPL);
        }

        public static bool GetNoDispCPL()
        {
            return IsOptionOpened(systemSubKey, "NoDispCPL");
        }

        public static bool GetNoSetFolders()
        {
            return IsOptionOpened(explorerSubKey, "NoSetFolders");
        }

        public static void SetNoSetFolders(bool noSetFolders)
        {
            OpenOption(explorerSubKey, "NoSetFolders", noSetFolders);
        }

        public static bool GetDisableRegistryTools()
        {
            return IsOptionOpened(systemSubKey, "DisableRegistryTools");
        }

        public static void SetDisableRegistryTools(bool disableRegistryTools)
        {
            OpenOption(systemSubKey, "DisableRegistryTools", disableRegistryTools);
        }

        private static Int32 GetNoDrivesValue(SortedDictionary<string, bool> driveVisibilityDict)
        {
            Int32 value = 0;

            foreach (var item in driveVisibilityDict)
            {
                if (noDrivesDict.ContainsKey(item.Key))
                {
                    IntUtil.TriggleBits(ref value, noDrivesDict[item.Key], !item.Value);
                }
            }

            return value;
        }

        private static Int32 GetInt32Value(string keyName, string valueName, Int32 defaultValue)
        {
            try
            {
                object value = Registry.GetValue(keyName, valueName, defaultValue);
                return value != null ? (Int32)value : defaultValue;
            }
            catch (Exception)
            {
                return defaultValue;
            }
        }

        private static bool IsOptionOpened(string keyName, string valueName)
        {
            Int32 value = GetInt32Value(keyName, valueName, 0);
            return IntUtil.IsBitsSet(value, 0x00000001);
        }

        private static void OpenOption(string keyName, string valueName, bool open)
        {
            Int32 value = GetInt32Value(keyName, valueName, 0);
            IntUtil.TriggleBits(ref value, 0x00000001, open);

            Registry.SetValue(keyName, valueName, value, RegistryValueKind.DWord);
        }
    }
}
