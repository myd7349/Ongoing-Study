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
            _tprintf(_T("Argument %d: %s\n"), i, argv[i]);

        LocalFree(argv);
    }

    if (stream != NULL)
        fclose(stream);

    return 0;
}


// References:
// [How to get the command line arguments in MFC applications?](https://stackoverflow.com/questions/5562877/how-to-get-the-command-line-arguments-in-mfc-applications)
// https://github.com/reactos/reactos/blob/be8e5fc7b31d64732a0ffd37a27d580c68c76ac5/dll/win32/shell32/wine/shell32_main.c#L80-L311
