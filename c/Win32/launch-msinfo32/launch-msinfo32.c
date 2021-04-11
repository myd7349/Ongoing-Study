#include <tchar.h>

#include "Execute.h"


int _tmain(void)
{
    ExecAppSync(_T("msinfo32.exe"), NULL, FALSE);

    return 0;
}
