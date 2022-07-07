#include <stdio.h>
#include <windows.h>

#include "bar.h"


typedef void (BAR_API *PBAR)(void);

int main(void)
{
    HMODULE hBar;
    PBAR bar;

    puts("Hello from main.");

    hBar = LoadLibraryA("bar.dll");
    if (hBar == NULL)
    {
        printf("Failed to load bar.dll: %d\n",
            (int)GetLastError());
        return 1;
    }

    bar = GetProcAddress(hBar, "Bar");
    if (bar != NULL)
    {
        bar();
    }
    else
    {
        printf("GetProcAddress failed: %d\n", (int)GetLastError());
    }

    FreeLibrary(hBar);

    return 0;
}


// References:
// [DLL Load Library - Error Code 126](https://stackoverflow.com/questions/14361992/dll-load-library-error-code-126)
// [Dynamic-Link Library Search Order](https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-search-order)
// [Runtime-load A DLL In The Same Directory (Not The Application Directory)](https://stackoverflow.com/questions/65164968/runtime-load-a-dll-in-the-same-directory-not-the-application-directory)
// [where is LoadLibrary A looking for the file?](https://stackoverflow.com/questions/14031749/where-is-loadlibrary-a-looking-for-the-file)
