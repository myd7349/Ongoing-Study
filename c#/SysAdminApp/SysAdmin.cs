// 2016-01-30T15:09+08:00
// By myd

using System;
using System.Collections.Generic;
using System.Linq;
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
                string driveName = name + @":\";
                noDrivesDict[name + @":\"] = mask;
                mask <<= 1;
            }
 
            noDrivesDict["All"] = 0x03FFFFFF;
        }

        public static SortedDictionary<string, bool> GetDriveVisibilityDict()
        {
            Int32 noDrivesValue = 0;
            try
            {
                object value = Registry.GetValue(explorerSubKey, "NoDrives", 0);
                noDrivesValue = value != null ? (Int32)value : 0;
            }
            catch (Exception)
            {
            }

            var dict = new SortedDictionary<string, bool>();
            foreach (var driveInfo in System.IO.DriveInfo.GetDrives())
            {
                string driveName = driveInfo.Name;
                dict[driveName] = !noDrivesDict.ContainsKey(driveName)
                    || (noDrivesValue & noDrivesDict[driveName]) == 0;
            }

            return dict;
        }

        public static void NoDrives(SortedDictionary<string, bool> driveVisibilityDict)
        {
            Registry.SetValue(explorerSubKey, "NoDrives", 
                GetNoDrivesValueFromDriveVisibilityDict(driveVisibilityDict), 
                RegistryValueKind.DWord);
        }

        private static Int32 GetNoDrivesValueFromDriveVisibilityDict(SortedDictionary<string, bool> driveVisibilityDict)
        {
            Int32 value = 0;

            foreach (var item in driveVisibilityDict)
            {
                if (!noDrivesDict.ContainsKey(item.Key))
                    continue;

                if (item.Value)
                    value &= ~noDrivesDict[item.Key];
                else
                    value |= noDrivesDict[item.Key];
            }

            return value;
        }
    }
}
