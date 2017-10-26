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

void CComboBox_Assign(CComboBox &ctrlComboBox, const CStringArray &arrstrItems)
{
    ASSERT(ctrlComboBox.GetSafeHwnd() != NULL);

    ctrlComboBox.Clear();
    for (int i = 0; i < arrstrItems.GetCount(); ++i)
        ctrlComboBox.AddString(arrstrItems[i]);
}

void CComboBox_CopyTo(const CComboBox &ctrlComboBox, CStringArray &arrstrItems)
{
    ASSERT(ctrlComboBox.GetSafeHwnd() != NULL);

    arrstrItems.RemoveAll();
    arrstrItems.SetSize(ctrlComboBox.GetCount());

    CString strItem;

    for (int i = 0; i < ctrlComboBox.GetCount(); ++i)
    {
        ctrlComboBox.GetLBText(i, strItem);
        arrstrItems[i] = strItem;
    }
}

CString CComboBox_GetSelectedString(const CComboBox &ctrlComboBox)
{
    ASSERT(ctrlComboBox.GetSafeHwnd() != NULL);

    int nCurSel = ctrlComboBox.GetCurSel();
    CString strSelectedItem;

    if (nCurSel != CB_ERR)
        ctrlComboBox.GetLBText(nCurSel, strSelectedItem);

    return strSelectedItem;
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

CArchive &operator>>(CArchive &ar, CStringArray &strings)
{
    int nCount = 0;
    
    ar >> nCount;
    strings.SetSize(nCount);

    CString str;

    for (int i = 0; i < nCount; i++)
    {
        ar >> str;
        strings[i] = str;
    }

    return ar;
}

CArchive &operator<<(CArchive &ar, const CStringArray &strings)
{
    ar << strings.GetCount();

    for (int i = 0; i < strings.GetCount(); ++i)
        ar << strings[i];

    return ar;
}

COLORREF GetColor(COLORREF clr)
{
    CColorDialog dlgColor;
    dlgColor.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
    dlgColor.m_cc.rgbResult = clr;

    dlgColor.DoModal();

    return dlgColor.m_cc.rgbResult;
}

// CListCtrl::IsItemVisible???
BOOL CListCtrl_IsItemVisible(const CListCtrl &ctrl, int nItem)
{
    ASSERT(ctrl.GetSafeHwnd() != NULL);
    int nFirstVisibleItem = ctrl.GetTopIndex();
    int nLastVisibleItem = nFirstVisibleItem + ctrl.GetCountPerPage();
    return nItem >= nFirstVisibleItem && nItem < nLastVisibleItem;
}
