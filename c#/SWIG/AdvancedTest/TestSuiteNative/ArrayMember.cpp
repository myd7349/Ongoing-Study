#include "ArrayMember.h"
#include "Win32Common.h"

void GetPath(Buffer buffer)
{
    GetModuleFileName(NULL, buffer.Path, ARRAYSIZE(buffer.Path));
}