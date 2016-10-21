// 2016-10-21T08:44+08:00
// Tools like `StampVer.exe` accept commandline arguments of format:
// StampVer.exe -k -p"1.2.3.4" -f"1.2.3.4" MyModule.dll
// So let's try out:
// msvc_cmdline_args.exe -p"1.2.3.4" -f"1.2.3.4"
//
#include <iostream>

#if defined(_MSC_VER)
#define STRICT 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << std::endl;

#if defined(_MSC_VER)
    std::cout << GetCommandLineA() << std::endl;
#endif

#if defined(_MSC_VER) && !defined(NDEBUG)
    std::cin.get();
#endif

    return 0;
}

/*
> msvc_cmdline_args.exe - p"1.2.3.4" - f"1.2.3.4"
msvc_cmdline_args.exe
-p1.2.3.4
-f1.2.3.4
msvc_cmdline_args.exe -p"1.2.3.4" -f"1.2.3.4"

> msvc_cmdline_args.exe -p\"1.2.3.4\" -f\"1.2.3.4\"
msvc_cmdline_args.exe
-p"1.2.3.4"
-f"1.2.3.4"
msvc_cmdline_args.exe -p\"1.2.3.4\" -f\"1.2.3.4\"
*/

/*
It seems that `StampVer.exe` itself calls `GetCommandLine` to get
the command line arguments.

When we spawning a `StampVer.exe` process with code below in Python:
>>> import subprocess
>>> cmd_args = ('StampVer.exe', '-k', '-f"{0}"'.format('1.2.3.4'), '-p"{0}"'.format('1.2.3.4'), 'MyModule.dll')
>>> subprocess.run(cmd_args)

we may not got it run properly.

Internally, `subprocess.run` calls `subprocess.list2cmdline` to join those 
command line arguments together. Then, the result is passed to CreateProcess
as its second parameter(suppose that `shell=False`).

>>> subprocess.list2cmdline(cmd_args)
'StampVer.exe -k -f\\"1.2.3.4\\" -p\\"1.2.3.4\\" MyModule.dll'
obviously that's not what `StampVer.exe` want.

*/

// Reference:
// https://msdn.microsoft.com/en-us/library/17w5ykft.aspx
// Python: subprocess.py/list2cmdline
// Ongoing-Study/python/SetPEVersion.py