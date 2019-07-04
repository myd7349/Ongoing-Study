<Query Kind="Program">
  <Namespace>System.Runtime.InteropServices</Namespace>
</Query>

[DllImport("msvcrt.dll", EntryPoint = "memset", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
public static extern IntPtr MemSet(IntPtr dest, int c, int byteCount);


void Main()
{
    var length = 10;
    
    var buffer = Marshal.AllocHGlobal(length * sizeof(byte));
    MemSet(buffer, 0x80, length * sizeof(byte));
    
    var array = new byte[length];
    Marshal.Copy(buffer, array, 0, length);
    
    Console.WriteLine(array);
    
    Marshal.FreeHGlobal(buffer);
}

// References:
// https://stackoverflow.com/questions/5486938/c-sharp-how-to-get-byte-from-intptr
// https://stackoverflow.com/questions/33323695/passing-byte-as-intptr-by-pinvoke-to-memset
// http://pinvoke.net/default.aspx/msvcrt/memset.html
