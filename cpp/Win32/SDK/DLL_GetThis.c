#include <tchar.h>
#include <Windows.h>


HMODULE DLL_GetThis()
{
    HMODULE hDLLThis = NULL;
    TCHAR szDir[MAX_PATH] = _T("");

    if(GetModuleHandleEx(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        szDir, &hDLLThis))
        return hDLLThis;

    return NULL;
}


// References:
// https://stackoverflow.com/questions/6924195/get-dll-path-at-runtime
// https://blog.assarbad.net/20090716/how-to-get-the-instance-handle-of-a-dll/
