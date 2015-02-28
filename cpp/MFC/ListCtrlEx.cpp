// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"

#include <locale.h>
#include <string.h>

#include <algorithm>
#include <iterator>

#pragma warning(disable: 4018)

// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CMFCListCtrl)

CListCtrlEx::CListCtrlEx()
{
    _tsetlocale(LC_ALL, _T(""));

    m_dummySortPolicy.trait = USRDEF;
    m_dummySortPolicy.func = DummySort;
}

CListCtrlEx::~CListCtrlEx()
{
}

int CListCtrlEx::InsertColumn(int nCol, const LVCOLUMN* pColumn, 
    SortTrait sortTrait, SortCallback sortFunc)
{
    // the return value of InsertColumn is not always equal to the value
    // you passed to it.
    // 1. 
    // If nCol < GetItemCount(), a new column will be inserted at
    // the nCol-th column. In this situation, the return value of
    // InsertColumn() will be equal to nCol.
    // 2.
    // If nCol >= GetItemCount(), then a new column will be append.
    // and the return value of InsertColumn() equals to GetItemCount().
    nCol = __super::InsertColumn(nCol, pColumn);
    if (nCol != -1)
    {
        ATLASSERT(nCol <= m_deqSortPolicies.size());
        if (nCol <= m_deqSortPolicies.size())
        {
            SortPolicy sortPolicy;
            sortPolicy.trait = sortTrait;
            sortPolicy.func = sortFunc;

            std::deque<SortPolicy>::iterator it = m_deqSortPolicies.begin();
            std::advance(it, nCol);
            m_deqSortPolicies.insert(it, sortPolicy);
        }
    }

    return nCol;
}

int CListCtrlEx::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, 
    int nFormat, int nWidth, int nSubItem, 
    SortTrait sortTrait, SortCallback sortFunc)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT|LVCF_FMT;
    column.pszText = (LPTSTR)lpszColumnHeading;
    column.fmt = nFormat;
    if (nWidth != -1)
    {
        column.mask |= LVCF_WIDTH;
        column.cx = nWidth;
    }
    if (nSubItem != -1)
    {
        column.mask |= LVCF_SUBITEM;
        column.iSubItem = nSubItem;
    }

    return InsertColumn(nCol, &column, sortTrait, sortFunc);
}

BOOL CListCtrlEx::DeleteColumn(int nCol)
{
    BOOL bRes = __super::DeleteColumn(nCol);
    if (bRes)
    {
        ATLASSERT(nCol < m_deqSortPolicies.size());
        if (nCol < m_deqSortPolicies.size())
        {
            std::deque<SortPolicy>::iterator it = m_deqSortPolicies.begin();
            std::advance(it, nCol);
            m_deqSortPolicies.erase(it);
        }
    }

    return bRes;
}

const CListCtrlEx::SortPolicy &CListCtrlEx::GetColumnSortPolicy(int nCol)
{
    if (nCol < m_deqSortPolicies.size())
    {
        return m_deqSortPolicies[nCol];
    }
    else
    {
        return m_dummySortPolicy;
    }
}

BOOL CListCtrlEx::SetColumnSortPolicy(int nCol, const SortPolicy &sortPolicy)
{
    if (nCol < m_deqSortPolicies.size())
    {
        m_deqSortPolicies[nCol] = sortPolicy;
        return TRUE;
    }
    
    return FALSE;
}

BOOL CListCtrlEx::SetColumnSortPolicy(int nCol, SortTrait sortTrait, SortCallback sortFunc)
{
    SortPolicy sortPolicy = { sortTrait, sortFunc };
    return SetColumnSortPolicy(nCol, sortPolicy);
}

BOOL CListCtrlEx::SetColumnSortPolicyArray(int nCount, SortPolicy *sortPolicyArray)
{
    if (nCount <= 0)
    {
        return FALSE;
    }

    if (nCount > m_deqSortPolicies.size())
    {
        nCount = m_deqSortPolicies.size();
    }
    
    std::copy(sortPolicyArray, sortPolicyArray + nCount, m_deqSortPolicies.begin());
    return TRUE;
}

#if 0
void CListCtrlEx::Sort(int iColumn, BOOL bAscending, BOOL bAdd)
{
    int iItemCnt = GetItemCount();

    m_deqItemsData.resize(iItemCnt);

    for (int i = 0; i < iItemCnt; ++i)
    {
        m_deqItemsData[i] = GetItemData(i);
        SetItemData(i, i);
    }

    __super::Sort(iColumn, bAscending, bAdd);

    // Restore items' data
    for (int i = 0; i < iItemCnt; ++i)
    {
        SetItemData(i, m_deqItemsData[i]);
    }
}
#else
void CListCtrlEx::Sort(int iColumn, BOOL bAscending, BOOL bAdd)
{
    int iItemCnt = GetItemCount();

    for (int i = 0; i < iItemCnt; ++i)
    {
        SetItemData(i, i);
    }

    __super::Sort(iColumn, bAscending, bAdd);
}
#endif

template <typename T>
int Compare(const T &lhs, const T &rhs)
{
    if (lhs < rhs)
    {
        return -1;
    }
    else if (rhs < lhs)
    {
        return 1;
    }

    return 0;
}

int CListCtrlEx::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
    SortPolicy sortPolicy = GetColumnSortPolicy(iColumn);
    if (USRDEF == sortPolicy.trait)
    {
        return sortPolicy.func(lParam1, lParam2);
    }
    else
    {
        CString strText1 = GetItemText(lParam1, iColumn);
        CString strText2 = GetItemText(lParam2, iColumn);

        switch (sortPolicy.trait)
        {
        case STRING:
            return _tcscoll(LPCTSTR(strText1), LPCTSTR(strText2));
        case NUMBER:
            {
                double dNum1 = _tcstod(LPCTSTR(strText1), NULL);
                double dNum2 = _tcstod(LPCTSTR(strText2), NULL);

                return Compare(dNum1, dNum2);
            } 
        default:
            ATLASSERT(FALSE);
            return __super::OnCompareItems(lParam1, lParam2, iColumn);
        }
    }
}

BEGIN_MESSAGE_MAP(CListCtrlEx, CMFCListCtrl)
END_MESSAGE_MAP()

// CListCtrlEx message handlers

