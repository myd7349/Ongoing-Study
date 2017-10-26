// 2016-11-22T11:40+08:00
#pragma once

void CComboBox_Clear(CComboBox &ctrlComboBox);
void CComboBox_Assign(CComboBox &ctrlComboBox, const CStringArray &arrstrItems);
void CComboBox_CopyTo(const CComboBox &ctrlComboBox, CStringArray &arrstrItems);
CString CComboBox_GetSelectedString(const CComboBox &ctrlComboBox);

void CEdit_MoveToEnd(CEdit &ctrlEdit);

CArchive &operator>>(CArchive &ar, CStringArray &strings);
CArchive &operator<<(CArchive &ar, const CStringArray &strings);

COLORREF GetColor(COLORREF clr);

BOOL CListCtrl_IsItemVisible(const CListCtrl &ctrl, int nItem);
