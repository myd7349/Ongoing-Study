#include "stdafx.h"
#include "MFCExtensions.h"

void CComboBox_Clear(CComboBox &ctrlComboBox)
{
    ASSERT(ctrlComboBox.GetSafeHwnd() != NULL);
    if (ctrlComboBox.GetSafeHwnd() == NULL)
        return;

    for (int i = ctrlComboBox.GetCount() - 1; i >= 0; i--)
        ctrlComboBox.DeleteString(i);
}

// http://www.stackoverflow.com/questions/1480873/cedit-control-mfc-placing-cursor-to-end-of-string-after-setwindowtext
void CEdit_MoveToEnd(CEdit &ctrlEdit)
{
    ASSERT(ctrlEdit.GetSafeHwnd() != NULL);
    if (ctrlEdit.GetSafeHwnd() == NULL)
        return;

    ctrlEdit.SetSel(0, -1);
    ctrlEdit.SetSel(-1);
}