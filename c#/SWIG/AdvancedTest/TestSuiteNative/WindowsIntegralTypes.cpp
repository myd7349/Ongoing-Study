#include "WindowsIntegralTypes.h"

void ToBeOrNotToBe(BOOL bToBe)
{
    MessageBoxW(NULL,
        bToBe ? L"To Be!" : L"Not To Be!",
        L"Windows Integral Types Test", MB_OK);
}
