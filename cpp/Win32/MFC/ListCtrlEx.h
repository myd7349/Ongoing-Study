// 2014-11-28T11:38+08:00
// By myd7349

#pragma once

#include <deque>

class CListCtrlEx : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)
public:
    enum SortTrait
    {
        STRING, // sort as string 
        NUMBER, // sort as number
        USRDEF, // user defined sort policy
    };

    typedef int (*SortCallback)(LPARAM, LPARAM);
    static int DummySort(LPARAM, LPARAM) { return 0; }

    struct SortPolicy
    {
        SortTrait    trait;
        SortCallback func;
    };

	CListCtrlEx();
	virtual ~CListCtrlEx();

    int InsertColumn(int nCol, const LVCOLUMN* pColumn, 
        SortTrait sortTrait = STRING, SortCallback sortFunc = DummySort);
    int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, 
        int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, 
        SortTrait sortTrait = STRING, SortCallback sortFunc = DummySort);
    BOOL DeleteColumn(int nCol);
    const SortPolicy &GetColumnSortPolicy(int nCol);
    BOOL SetColumnSortPolicy(int nCol, const SortPolicy &sortPolicy);
    BOOL SetColumnSortPolicy(int nCol, SortTrait sortTrait, SortCallback sortFunc = DummySort);
    BOOL SetColumnSortPolicyArray(int nCount, SortPolicy *sortPolicyArray);

    // Overrides
    virtual void Sort(int iColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE);
    virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);

private:
    std::deque<SortPolicy> m_deqSortPolicies;
    SortPolicy             m_dummySortPolicy;
    std::deque<DWORD_PTR>  m_deqItemsData;

protected:
	DECLARE_MESSAGE_MAP()
};
