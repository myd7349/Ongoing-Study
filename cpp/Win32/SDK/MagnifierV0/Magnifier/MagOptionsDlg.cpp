#include "stdafx.h"
#include "MagOptions.h"
#include "MagOptionsDlg.h"
#include "resource.h"


// Please refer to Jeffrey Richter's book.
#define HANDLE_DLGMSG(hwnd, message, fn)                     \
    case (message): return (SetDlgMsgResult(hwnd, message,   \
        HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


namespace
{
BOOL Cls_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
    Mag::Options options;
    Mag::Options::LoadEx(options);

    return TRUE;
}


void Cls_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    if (IDOK == id)
    {
        Mag::Options options;
        Mag::Options::LoadEx(options);
        Mag::Options::Save(options);

        EndDialog(hDlg, id);
    }
    else if (IDCANCEL == id)
    {
        EndDialog(hDlg, id);
    }
}

} // namespace -


INT_PTR CALLBACK OptionsDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    HANDLE_DLGMSG(hDlg, WM_INITDIALOG, Cls_OnInitDialog);
    HANDLE_DLGMSG(hDlg, WM_COMMAND, Cls_OnCommand);
    }

    return (INT_PTR)FALSE;
}
