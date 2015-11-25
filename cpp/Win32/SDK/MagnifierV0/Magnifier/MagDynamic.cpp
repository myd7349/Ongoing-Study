#include "stdafx.h"
#include "MagDynamic.h"
#include "Common/Utility.h"

namespace Mag
{

void MagDynamic::Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag)
{
    assert(hdc != NULL);
    
    // GetWindowDC(GetDesktopWindow());
    // GetDC(NULL);
    HDC hdcScreen = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
    assert(hdcScreen != NULL);
    
    StretchBlt(hdc, rcDest.left, rcDest.top, Utility::RCWidth(rcDest), Utility::RCHeight(rcDest), 
            hdcScreen, rcMag.left, rcMag.top, Utility::RCWidth(rcMag), Utility::RCHeight(rcMag), 
            SRCCOPY);
    
    DeleteDC(hdcScreen);
}
} // namespace Mag