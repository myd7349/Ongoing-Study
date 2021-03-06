#include "stdafx.h"
#include "MagOptions.h"

#include <stdio.h>
#include <string.h>

namespace Mag
{
const char *CONFIG_FILE = "Magnifier.dat";

void Options::Reset(Options &options)
{
    options.dwExStyle = 0; //WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_STATICEDGE;
    options.dwStyle = WS_OVERLAPPEDWINDOW; //WS_POPUP/* | WS_BORDER*/;
    options.style = MAGS_STATIC;
    options.mode = MAGM_DYNAMIC;
    options.clrFocus = RGB(0, 255, 128);
    options.clrBkgnd = RGB(0, 0, 0);
    options.clrText = RGB(0, 255, 0);
    options.clrReserved = 0;
    options.bAutoHide = FALSE;
    options.bShowFocus = TRUE;
    options.bShowFactor = FALSE;
    options.bShowPos = FALSE;
    options.bInvertColor = FALSE;
    options.bIsClientSize = TRUE;
    options.nWidth = 400;
    options.nHeight = 250;
    options.focus = MAGF_CROSS;
    options.nFocusSize = 10;
    options.dFactor = 2.0;
    options.dFactorMin = 0.2;
    options.dFactorMax = 5.0;
    _tcsncpy_s(options.szTitle, ARRAYSIZE(options.szTitle), 
        _T("�Ŵ�"), _tcslen(_T("�Ŵ�")));
}


BOOL Options::Load(Options &options)
{
    FILE *fp;
    if (fopen_s(&fp, CONFIG_FILE, "rb") != 0)
    {
        return FALSE;
    }

    size_t sz = fread(&options, sizeof(options), 1, fp);
    fclose(fp);

    if (sizeof(options) == sz)
    {
        if (_tcsnlen(options.szTitle, ARRAYSIZE(options.szTitle)) 
            == ARRAYSIZE(options.szTitle))
        {
            return FALSE;
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


void Options::LoadEx(Options &options)
{
    if (!Load(options))
    {
        Reset(options);
    }
}


BOOL Options::Save(const Options &options)
{
    FILE *fp;
    if (fopen_s(&fp, CONFIG_FILE, "wb") != 0)
    {
        return FALSE;
    }

    fwrite(&options, sizeof(options), 1, fp);
    fclose(fp);

    return TRUE;
}

} // namespace Mag