<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Management.dll</Reference>
  <Namespace>System.Management</Namespace>
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

[DllImport("kernel32.dll", EntryPoint = "FindFirstVolume", SetLastError = true, CallingConvention = CallingConvention.StdCall)]
public static extern int FindFirstVolume(StringBuilder lpszVolumeName, int cchBufferLength);

[DllImport("kernel32.dll", EntryPoint = "FindNextVolume", SetLastError = true, CallingConvention = CallingConvention.StdCall)]
public static extern bool FindNextVolume(int hFindVolume, StringBuilder lpszVolumeName, int cchBufferLength);

[DllImport("kernel32.dll", EntryPoint = "FindVolumeClose", SetLastError = true, CallingConvention = CallingConvention.StdCall)]
public static extern bool FindVolumeClose(int hFindVolume);

public static List<string> GetVolumes()
{
    const int N = 1024;
    StringBuilder cVolumeName = new StringBuilder((int)N);
    List<string> ret = new List<string>();
    int volume_handle = FindFirstVolume(cVolumeName, N);
    do
    {
        ret.Add(cVolumeName.ToString());
    } while (FindNextVolume(volume_handle, cVolumeName, N));

    FindVolumeClose(volume_handle);

    return ret;
}

    
string GetVolumnSerialNumber(char disk)
{
    var mo = new ManagementObject(string.Format("win32_logicaldisk.deviceid=\"{0}:\"", disk));
    mo.Get();
    return mo.GetPropertyValue("VolumeSerialNumber").ToString();
}


void Main()
{
    foreach (var volume in GetVolumes())
        Console.WriteLine(volume);
        
    foreach (var drive in DriveInfo.GetDrives())
    {
        Console.Write("{0}\t{1}\t", drive.Name, drive.DriveFormat);
        try
        {
            var serialNo = GetVolumnSerialNumber(drive.Name[0]);
            Console.WriteLine(serialNo);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

// References:
// [How to enumerate disk volume names?](https://stackoverflow.com/questions/29212597/how-to-enumerate-disk-volume-names)
// [Use unmanaged FindFirstVolume to enumerate volumes with .NET in C#](https://stackoverflow.com/questions/3981277/use-unmanaged-findfirstvolume-to-enumerate-volumes-with-net-in-c-sharp)
// [https://stackoverflow.com/questions/781905/getting-a-list-of-logical-drives](https://stackoverflow.com/questions/781905/getting-a-list-of-logical-drives)
