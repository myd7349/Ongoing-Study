#include <stdio.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>


int _tmain(void)
{
    int argc;
    PWSTR *argv;
    int i;
    PWSTR pszCommandLine = GetCommandLineW();
    FILE *stream = NULL;

    _tfreopen_s(&stream, _T("output.txt"), _T("w"), stdout);
    //if (stream != NULL)
    //    fclose(stdout);
    // Uncomment these two lines above, the program will crash.

    _putts(pszCommandLine);

    argv = CommandLineToArgvW(pszCommandLine, &argc);
    if (argv != NULL)
    {
        for (i = 0; i < argc; ++i)
            _tprintf(_T("Argument %d: %s, address: %p\n"), i, argv[i], argv[i]);

        LocalFree(argv);
    }

    if (stream != NULL)
        fclose(stream);

    return 0;
}


// References:
// [How to get the command line arguments in MFC applications?](https://stackoverflow.com/questions/5562877/how-to-get-the-command-line-arguments-in-mfc-applications)
// https://github.com/reactos/reactos/blob/be8e5fc7b31d64732a0ffd37a27d580c68c76ac5/dll/win32/shell32/wine/shell32_main.c#L80-L311
// https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-commandlinetoargvw
// > The address returned by CommandLineToArgvW is the address of the first element in an array of LPWSTR values;
// > the number of pointers in this array is indicated by pNumArgs. Each pointer to a null-terminated Unicode string
// > represents an individual argument found on the command line.
// >
// > CommandLineToArgvW allocates a block of contiguous memory for pointers to the argument strings, and for the
// > argument strings themselves; the calling application must free the memory used by the argument list when it
// > is no longer needed. To free the memory, use a single call to the LocalFree function.
// [Canonical way to parse the command line into arguments in plain C Windows API](https://stackoverflow.com/questions/291424/canonical-way-to-parse-the-command-line-into-arguments-in-plain-c-windows-api)
// https://github.com/reactos/reactos/blob/9b716539182864bc077e362febcda74da50287ed/dll/win32/shell32/wine/shell32_main.c#L80-L311
// explain how CommandLineToArgvW works.
// https://github.com/f3d-app/f3d/blob/master/application/main.cxx
