#include <stdio.h>
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>


typedef int(__cdecl *AddIProcT)(int a, int b);


int _tmain(int argc, _TCHAR *argv[])
{
    AddIProcT AddI;
    HMODULE hModule = LoadLibrary(_T("HelloCSharp.dll"));
    if (hModule != NULL)
    {
        AddI = (AddIProcT)GetProcAddress(hModule, "AddI");
        if (AddI != NULL)
            _tprintf(_T("1 + 1 = %d\n"), AddI(1, 1));
        else
            _tprintf(_T("GetProcAddress failed: %u.\n"), GetLastError());

        FreeLibrary(hModule);
    }
    else
    {
        _tprintf(_T("LoadLibrary failed: %u.\n"), GetLastError());
    }

    _tsystem(_T("pause"));

    return 0;
}


// References:
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [Unmanaged Exports](https://sites.google.com/site/robertgiesecke/Home/uploads/unmanagedexports) - [NuGet package](https://www.nuget.org/packages/UnmanagedExports)
// [DllExport](https://github.com/3F/DllExport)
// https://github.com/3F/Examples/tree/master/DllExport/BasicExport
