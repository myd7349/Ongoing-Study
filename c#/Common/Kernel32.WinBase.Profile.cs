namespace Common
{
    using System;
    //using System.ComponentModel;
    using System.Linq;
    using System.Runtime.InteropServices;

    public static class Kernel32
    {
        [DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Auto)]
        public static extern uint GetPrivateProfileInt(string lpAppName, string lpKeyName, int nDefault, string lpFileName);

        [DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Auto)]
        public static extern uint GetPrivateProfileSection(string lpAppName, [Out] IntPtr lpReturnedString, uint nSize, string lpFileName);

        //[DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Auto)]
        //private static extern uint GetPrivateProfileSectionW(string lpAppName, StringBuilder lpReturnedString, uint nSize, string lpFileName);

        //[DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Unicode)]
        //private static extern unsafe uint GetPrivateProfileSectionW(string lpAppName, [Out] char* lpReturnedString, uint nSize, string lpFileName);

        [DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Unicode)]
        private static extern uint GetPrivateProfileSectionW(string lpAppName, [Out] char[] lpReturnedString, uint nSize, string lpFileName);

        public static string[] GetPrivateProfileSection(string lpAppName, string lpFileName)
        {
            return ReadString(
                buffer => GetPrivateProfileSectionW(lpAppName, buffer, (uint)buffer.Length, lpFileName),
                IsBufferTooSmall).ToStrings().ToArray();
        }

        [DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Auto)]
        public static extern uint GetPrivateProfileSectionNames(IntPtr lpszReturnBuffer, uint nSize, string lpFileName);

        [DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Unicode)]
        private static extern uint GetPrivateProfileSectionNamesW([Out] char[] lpszReturnBuffer, uint nSize, string lpFileName);

        public static string[] GetPrivateProfileSectionNames(string lpFileName)
        {
            return ReadString(
                buffer => GetPrivateProfileSectionNamesW(buffer, (uint)buffer.Length, lpFileName),
                IsBufferTooSmall).ToStrings().ToArray();
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern uint GetPrivateProfileString(string lpAppName, string lpKeyName, string lpDefault, IntPtr lpReturnedString, uint nSize, string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern uint GetPrivateProfileStringW(string lpAppName, string lpKeyName, string lpDefault, char[] lpReturnedString, uint nSize, string lpFileName);

        public static string GetPrivateProfileString(string lpAppName, string lpKeyName, string lpDefault, string lpFileName)
        {
            return ReadString(
                buffer =>
                {
                    var result = GetPrivateProfileStringW(lpAppName, lpKeyName, lpDefault, buffer, (uint)buffer.Length, lpFileName);
#if false
                    var lastError = Marshal.GetLastWin32Error();
                    if (lastError != 0)
                        throw new Win32Exception(lastError);
#endif
                    return result;
                },
                (buffer, result) => result == buffer.Length - 2 || result == buffer.Length - 1);
        }

        [DllImport("kernel32.dll", SetLastError = false, CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetPrivateProfileStruct(string lpszSection, string lpszKey, IntPtr lpStruct, uint uSizeStruct, string szFile);

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool WritePrivateProfileSection(string lpAppName, IntPtr lpString, string lpFileName);

        /*
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool WritePrivateProfileSection(
            string lpAppName,
            [In, MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NullTermStringArrayMarshaler), MarshalCookie = "Auto")] string[] lpString,
            string lpFileName);
        */
        // According to:
        // https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-writeprivateprofilesectionw
        // lpString
        // The new key names and associated values that are to be written to the named section.This string is limited to 65,535 bytes.
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool WritePrivateProfileSection(string lpAppName, string lpString, string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool WritePrivateProfileString(string lpAppName, string lpKeyName, string lpString, string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool WritePrivateProfileStruct(string lpszSection, string lpszKey, [In] IntPtr lpStruct, uint uSizeStruct, string szFile);

        private const int StringBufferLengthHint = 256;

        private const int StringBufferMaximumLength = ushort.MaxValue + 3;

        private static string ReadString(
            Func<char[], uint> read,
            Func<char[], uint, bool> isBufferTooSmall)
        {
            // TODO:
            // Will using System.Buffers.ArrayPool<char> here improve performance?
            var buffer = new char[StringBufferLengthHint];

            while (true)
            {
                uint result = read(buffer);

                if (result == 0)
                    return string.Empty;

                if (!isBufferTooSmall(buffer, result))
                    return new string(buffer, 0, (int)result);

                if (buffer.Length == StringBufferMaximumLength)
                    throw new InsufficientMemoryException();

                var newBufferLength = Math.Min(buffer.Length * 2, StringBufferMaximumLength);
                buffer = new char[newBufferLength];
            }
        }

        private static bool IsBufferTooSmall(char[] buffer, uint result)
        {
            return result == buffer.Length - 2;
        }
    }
}


// References:
// https://github.com/dotnet/pinvoke/blob/master/src/Kernel32/Kernel32.exports.txt
/*
GetPrivateProfileInt
GetPrivateProfileSection
GetPrivateProfileSectionNames
GetPrivateProfileString
GetPrivateProfileStruct

WritePrivateProfileSection
WritePrivateProfileString
WritePrivateProfileStruct
 */
// https://github.com/dahall/Vanara/blob/56cda5a8f4d6648563651996d99f471f9e49e56f/PInvoke/Kernel32/WinBase.Profile.cs
// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getprivateprofileint
// https://github.com/dotnet/pinvoke/blob/master/src/Windows.Core/ApiSets.cs
// https://github.com/dotnet/pinvoke/blob/master/src/Kernel32/Kernel32.cs
// https://github.com/dotnet/pinvoke/blob/bc93e82c2208023ac142acb6a2a26ca3f59fc40a/src/User32/User32.cs#L2994-L2998
// https://github.com/dotnet/pinvoke/blob/bc93e82c2208023ac142acb6a2a26ca3f59fc40a/src/User32/User32.Helpers.cs#L314
// Ongoing-Study\c#\Console\PInvoke\FunctionPointerTest\FunctionPointerTest\Program.cs
// https://docs.microsoft.com/en-us/dotnet/api/system.runtime.interopservices.marshal.getlastwin32error?view=net-5.0
// [Reset GetLastError value](https://stackoverflow.com/questions/6558578/reset-getlasterror-value)
// [CA1838: Avoid StringBuilder parameters for P/Invokes](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1838)
// https://www.codeproject.com/Questions/242867/Doubt-in-INI-file-reading
/*
long ReadIntegerValueFromIni( const CString& csAppName_i,
                              const CString& csKeyName_i,
                              const CString& csDefaultVal_i,
                              const CString& csFileName_i,
                              const int nMinVal_i,
                              const int nMaxVal_i )
{
    long lKeyValue = 0;
    int nDefaultVal = _ttoi( csDefaultVal_i );
    try
    {
        const int SUCCESS_RET = 1;
        TCHAR tcszBuf[ MAX_PATH ];
        TCHAR tcszBufTemp[ MAX_PATH ];
        lKeyValue = nDefaultVal;

        // Read the value from INI file.
        GetPrivateProfileString( csAppName_i, csKeyName_i, csDefaultVal_i, tcszBuf, sizeof( tcszBuf ),
                                 csFileName_i );
        // Check whether the value read from ini is a valid numeric number or not.
        if( SUCCESS_RET != swscanf( tcszBuf, _T( "%d%s" ), &lKeyValue, &tcszBufTemp ))
        {
            lKeyValue = nDefaultVal;
            // Invalid value found so adjusted to Default Value.
        }
        // Check whether the value read from ini is within the allowed range or not.
        else if( nMinVal_i > lKeyValue || nMaxVal_i < lKeyValue )
        {
            lKeyValue = nDefaultVal;
            // Input value is not within the allowed range, so adjusted to Default Value
        }
        else
        {
            // Do nothing.
        }
    }
    catch( ... )
    {
        // Unhandled exception occured in ReadIntegerValueFromIni()
        lKeyValue = nDefaultVal;
    }
    return lKeyValue;
}
*/
// [GetPrivateProfileString - Buffer length](https://stackoverflow.com/questions/10507927/getprivateprofilestring-buffer-length)
// [Help with \0 terminated strings in C#](https://stackoverflow.com/questions/2581325/help-with-0-terminated-strings-in-c-sharp)
