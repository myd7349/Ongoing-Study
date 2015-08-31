
// DBVListTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBVListTest.h"
#include "DBVListTestDlg.h"
#include "afxdialogex.h"
#include "SearchDlg.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int MARGIN = 10;
const int BUTTON_WIDTH = 75;
const int BUTTON_HEIGHT = 25;
const int BUTTON_COUNT = 5;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDBVListTestDlg dialog

CDBVListTestDlg::CDBVListTestDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDBVListTestDlg::IDD, pParent), m_bASC(TRUE)
#if USE_ITEM_CACHE_HINT
    , m_iMainCacheStart(-1), m_iEndAreaCacheStart(-1)
#endif
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBVListTestDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EMP_LIST, m_ctrlEmpList);
}

BEGIN_MESSAGE_MAP(CDBVListTestDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_EMP_LIST, &CDBVListTestDlg::OnLvnColumnclickEmpList)
    ON_NOTIFY(LVN_GETDISPINFO, IDC_EMP_LIST, &CDBVListTestDlg::OnLvnGetdispinfoEmpList)
#if USE_ITEM_CACHE_HINT
    ON_NOTIFY(LVN_ODCACHEHINT, IDC_EMP_LIST, &CDBVListTestDlg::OnLvnOdcachehintEmpList)
#endif
    ON_NOTIFY(LVN_ODFINDITEM, IDC_EMP_LIST, &CDBVListTestDlg::OnLvnOdfinditemEmpList)
    ON_WM_GETMINMAXINFO()
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BTN_ALL, &CDBVListTestDlg::OnBnClickedBtnAll)
    ON_BN_CLICKED(IDC_BTN_SEARCH, &CDBVListTestDlg::OnBnClickedBtnSearch)
    ON_BN_CLICKED(IDC_BTN_MODIFY, &CDBVListTestDlg::OnBnClickedBtnModify)
    ON_BN_CLICKED(IDC_BTN_DELETE, &CDBVListTestDlg::OnBnClickedBtnDelete)
    ON_NOTIFY(LVN_ENDLABELEDIT, IDC_EMP_LIST, &CDBVListTestDlg::OnLvnEndlabeleditEmpList)
END_MESSAGE_MAP()

void CDBVListTestDlg::GetDispInfo(LVITEM* pItem)
{
    // called when the list control needs to display data
    if(pItem->iItem >= 0 && (pItem->mask & LVIF_TEXT))
    {
        EmployeeItem *pEmpItem = RetrieveItem(pItem->iItem);
        if(pEmpItem != NULL)
        {
#define ASSIGN(text) Checked::_tcscpy_s(pItem->pszText, pItem->cchTextMax, text)
            // display the appropriate column
            switch(pItem->iSubItem)
            {
            case 0: ASSIGN((LPCTSTR)pEmpItem->m_Email); break;
            case 1: ASSIGN((LPCTSTR)pEmpItem->m_Name); break;
            case 2: ASSIGN((LPCTSTR)pEmpItem->m_Phone); break;
            case 3: ASSIGN((LPCTSTR)pEmpItem->m_Location); break;
            case 4: ASSIGN((LPCTSTR)pEmpItem->m_Title); break;
            case 5: ASSIGN((LPCTSTR)pEmpItem->m_Department); break;
            case 6: ASSIGN((LPCTSTR)pEmpItem->m_Division); break;
            default: break;
            }
        }
    }
}

#if USE_ITEM_CACHE_HINT
// http://www.codeproject.com/Articles/7891/Using-virtual-lists
// >LVN_ODCACHEHINT is sent to give you a chance to cache data. If you are working
// with a database that is in another computer in some network, maybe this is useful
void CDBVListTestDlg::PrepareCache(int iFrom, int iTo)
{
    ATLTRACE(_T("iFrom: %d, iTo: %d\n"), iFrom, iTo);
    // The cache algorithm found in MSDN/Using List-View Controls

    // Check to see if this is the end cache
    if (iTo == m_ctrlEmpList.GetItemCount() - 1 && iTo - iFrom < 30) { // 30 entries wide
        // Check to see if this is a portion of the current end cache.
        if (m_vEndAreaCache.size() > 0
            && iFrom >= m_iEndAreaCacheStart
            && iFrom < m_iEndAreaCacheStart + (int)m_vEndAreaCache.size())
            // If it is a part of current end cache, no loading is necessary.
            return;

        // In order to update record count, we move
        // to the last record in CEmployeeSet::SetFilter.
        // So we can not replace the call to MoveFirst+Move
        // with a single call to SetAbsolutePosition.
        //m_DBVListSet.SetAbsolutePosition(iFrom);
        m_DBVListSet.MoveFirst();
        m_DBVListSet.Move(iFrom);

        // This is a new end cache.
        m_iEndAreaCacheStart = iFrom;
        m_vEndAreaCache.resize(iTo - iFrom + 1);
        std::size_t i = 0;
        for (; i < m_vEndAreaCache.size(); ++i) {
            m_vEndAreaCache[i] = m_DBVListSet.m_EmpItem;
            if (m_DBVListSet.IsEOF())
                break;
            m_DBVListSet.MoveNext();
        }
        m_vEndAreaCache.resize(i);
    } else {
        // It is not a member of the current end cache
        // Try the primary cache instead.

        // Check to see if iFrom is within the primary cache.
        BOOL bOLFrom = m_vMainCache.size() > 0 
            && iFrom >= m_iMainCacheStart 
            && iFrom < m_iMainCacheStart + (int)m_vMainCache.size();
        // Check to see if iTo is within the primary cache.
        BOOL bOLTo = m_vMainCache.size() > 0 
            && iTo >= m_iMainCacheStart 
            && iTo < m_iMainCacheStart + (int)m_vMainCache.size();

        // If both iFrom and iTo are within current cache, no work is needed.
        if (bOLFrom && bOLTo)
            return;

        // Enlarge the cache size rather than make it specific to this hint.
        if (bOLFrom)
            iFrom = m_iMainCacheStart;
        else if (bOLTo)
            iTo = m_iMainCacheStart + m_vMainCache.size();

        // Set the index and count values for the new primary cache, and
        // then retrieve the memory.
        m_iMainCacheStart = iFrom;
        m_vMainCache.resize(iTo - iFrom + 1);

        ATLTRACE(_T("iFrom2: %d, iTo2: %d\n"), iFrom, iTo);

        m_DBVListSet.MoveFirst();
        m_DBVListSet.Move(iFrom);

        // Loop to fill the cache with the recommended items
        std::size_t i = 0;
        for (; i < m_vMainCache.size(); ++i) {
            m_vMainCache[i] = m_DBVListSet.m_EmpItem;
            if (m_DBVListSet.IsEOF())
                break;
            m_DBVListSet.MoveNext();
        }
        m_vMainCache.resize(i);
    }
}
#endif

PEmployeeItem CDBVListTestDlg::RetrieveItem(int iItem)
{
    if (iItem < 0)
        return NULL;

#if USE_ITEM_CACHE_HINT
    // Check to see if the item is in the main cache.
    if (iItem >= m_iMainCacheStart 
        && iItem < m_iMainCacheStart + (int)m_vMainCache.size()) {
            // The item is in the main cache.
            ATLTRACE(_T("From main cache.\n"));
            return &m_vMainCache[iItem - m_iMainCacheStart];
    } else if (iItem >= m_iEndAreaCacheStart
        && iItem < m_iEndAreaCacheStart + (int)m_vEndAreaCache.size()) {
            // The item is in the end area cache.
            ATLTRACE(_T("From end cache.\n"));
            return &m_vEndAreaCache[iItem - m_iEndAreaCacheStart];
    }

    ATLTRACE(_T("Not cached.\n"));
#endif

    // move to the appropriate row in the database
    m_DBVListSet.MoveFirst();
    m_DBVListSet.Move(iItem);

    if (m_DBVListSet.IsEOF())
        return NULL;
    else
        return &m_DBVListSet.m_EmpItem;
}

void CDBVListTestDlg::UpdateFilter(CString strCurQuery, BOOL bUpdate)
{
    // convenience function to set the SQL filter for the query
    m_DBVListSet.SetFilter(strCurQuery, bUpdate);

    // set the item count to the new record count
    int nRecordCount = 0;
    if (m_DBVListSet.IsOpen())
    {
        nRecordCount = m_DBVListSet.GetRecordCount();
    }

    m_ctrlEmpList.SetItemCountEx(nRecordCount);
    // Invalidate the list control so it will redraw itself
    m_ctrlEmpList.Invalidate();
}

std::size_t CDBVListTestDlg::GetFieldInfos(std::vector<CODBCFieldInfo> &vFieldInfos)
{
    vFieldInfos.clear();

    if (!m_DBVListSet.IsOpen() && !m_DBVListSet.Open())
        return 0;

    std::size_t cols = m_DBVListSet.GetODBCFieldCount();
    for (std::size_t i = 0; i < cols; ++i) {
        CODBCFieldInfo fieldInfo;
        m_DBVListSet.GetODBCFieldInfo(i, fieldInfo);
        vFieldInfos.push_back(fieldInfo);
    }

    return cols;
}

void CDBVListTestDlg::InitListControl()
{
    if (m_ctrlEmpList.GetSafeHwnd() == NULL)
        return;

    m_ctrlEmpList.ModifyStyle(0, LVS_EDITLABELS);
    m_ctrlEmpList.SetExtendedStyle(LVS_EX_FLATSB 
        //| LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE
        | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_AUTOSIZECOLUMNS
        | LVS_EX_DOUBLEBUFFER);

    std::vector<CODBCFieldInfo> vFieldInfos;
    int iColumns = static_cast<int>(GetFieldInfos(vFieldInfos));
    for (int i = 0; i < iColumns; ++i) {
        m_ctrlEmpList.InsertColumn(i, vFieldInfos[i].m_strName, LVCFMT_LEFT, 100);
    }
}

// CDBVListTestDlg message handlers

BOOL CDBVListTestDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

    InitListControl();
    UpdateFilter(_T(""), TRUE);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDBVListTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDBVListTestDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDBVListTestDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CDBVListTestDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    lpMMI->ptMinTrackSize.x = BUTTON_COUNT * (BUTTON_WIDTH + MARGIN) + MARGIN * 3;
    lpMMI->ptMinTrackSize.y = BUTTON_WIDTH + MARGIN * 4;

    CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CDBVListTestDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    if (GetDlgItem(IDC_EMP_LIST) == NULL)
        return;

    CRect rcClient;
    GetClientRect(rcClient);

    CRect rcListCtrl;
    rcListCtrl.SetRect(0, 0, 
        rcClient.Width() - 2 * MARGIN, 
        rcClient.Height() - 3 * MARGIN - BUTTON_HEIGHT);
    rcListCtrl.MoveToXY(MARGIN, MARGIN);

    m_ctrlEmpList.MoveWindow(rcListCtrl);

    CRect rcButton;
    rcButton.SetRect(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);

    int iButtons[BUTTON_COUNT] = {IDOK, IDC_BTN_DELETE, IDC_BTN_SEARCH, IDC_BTN_MODIFY, IDC_BTN_ALL};
    for (int i = 0; i < ARRAYSIZE(iButtons); ++i) {
        ASSERT(iButtons[i] != 0);
        rcButton.MoveToXY(
            rcClient.right - (i + 1) * (BUTTON_WIDTH + MARGIN),
            rcClient.bottom - (BUTTON_HEIGHT + MARGIN));
        CWnd *pWnd = GetDlgItem(iButtons[i]);
        ATLASSERT(pWnd != NULL);
        pWnd->MoveWindow(rcButton);
        pWnd->Invalidate();
    }

    Invalidate();
}

void CDBVListTestDlg::OnLvnColumnclickEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    ////
    TCHAR szText[128];
    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT;
    lvc.pszText = szText;
    lvc.cchTextMax = ARRAYSIZE(szText);
    m_ctrlEmpList.GetColumn(pNMLV->iSubItem, &lvc);

    CString strFilter;
    strFilter.Format(_T("[%s]"), lvc.pszText);
    strFilter += m_bASC ? _T(" ASC") : _T(" DESC");
    m_DBVListSet.SetSort(strFilter);

    m_ctrlEmpList.Invalidate();

    m_bASC = !m_bASC;
    ////
    *pResult = 0;
}

void CDBVListTestDlg::OnLvnGetdispinfoEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
    GetDispInfo(&pDispInfo->item);
    *pResult = 0;
}

#if USE_ITEM_CACHE_HINT
void CDBVListTestDlg::OnLvnOdcachehintEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLVCACHEHINT pCacheHint = reinterpret_cast<LPNMLVCACHEHINT>(pNMHDR);
    PrepareCache(pCacheHint->iFrom, pCacheHint->iTo);
    *pResult = 0;
}
#endif

void CDBVListTestDlg::OnLvnOdfinditemEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLVFINDITEM pFindInfo = reinterpret_cast<LPNMLVFINDITEM>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}

void CDBVListTestDlg::OnLvnEndlabeleditEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

    if (pDispInfo->item.pszText != NULL) {
        m_DBVListSet.Edit();
        m_DBVListSet.m_EmpItem.m_Email = pDispInfo->item.pszText;
        if (!m_DBVListSet.Update())
            AfxMessageBox(_T("Failed to update record!"));
        UpdateFilter(m_DBVListSet.m_strFilter, TRUE);
    }

    *pResult = 0;
}

void CDBVListTestDlg::OnBnClickedBtnAll()
{
    UpdateFilter(_T(""), TRUE);
}

void CDBVListTestDlg::OnBnClickedBtnSearch()
{
    std::vector<CODBCFieldInfo> vFieldInfos;
    GetFieldInfos(vFieldInfos);

    CSearchDlg searchDlg(vFieldInfos);
    if (searchDlg.DoModal() == IDOK) {
        UpdateFilter(searchDlg.GetFilter());
    }
}

void CDBVListTestDlg::OnBnClickedBtnModify()
{
}

void CDBVListTestDlg::OnBnClickedBtnDelete()
{
    POSITION pos = m_ctrlEmpList.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;

    CString strNewFilter = _T("[Email] in (");
    CString strEmail;
    BOOL bFirstSelItem = TRUE;
    while (pos) {
        int iItem = m_ctrlEmpList.GetNextSelectedItem(pos);
        strEmail = m_ctrlEmpList.GetItemText(iItem, 0);
        if (bFirstSelItem) {
            strNewFilter += QuotedValue(strEmail);
            bFirstSelItem = FALSE;
        } else {
            strNewFilter += _T(", ") + QuotedValue(strEmail);
        }
    }
    strNewFilter += _T(')');

    ATLASSERT(m_DBVListSet.IsOpen());
    CString strPrevFilter = m_DBVListSet.m_strFilter;
    UpdateFilter(strNewFilter);
    m_DBVListSet.MoveFirst();

    if (m_DBVListSet.IsEOF() 
        || !m_DBVListSet.CanUpdate() || !m_DBVListSet.CanTransact()) {
        UpdateFilter(strPrevFilter);
        return;
    }

    CDatabase *pDatabase = m_DBVListSet.m_pDatabase;
    ATLASSERT(pDatabase != NULL);
    pDatabase->BeginTrans();

    TRY {
        while (!m_DBVListSet.IsEOF()) {
            m_DBVListSet.Delete();
            m_DBVListSet.MoveNext();
        }

        pDatabase->CommitTrans();
    } CATCH_ALL (e) {
        pDatabase->Rollback();
    }
    END_CATCH_ALL

    UpdateFilter(strPrevFilter);
}
