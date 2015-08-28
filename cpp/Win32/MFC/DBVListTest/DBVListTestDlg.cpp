
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
	: CDialogEx(CDBVListTestDlg::IDD, pParent)
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
    ON_NOTIFY(LVN_ODCACHEHINT, IDC_EMP_LIST, &CDBVListTestDlg::OnLvnOdcachehintEmpList)
    ON_NOTIFY(LVN_ODFINDITEM, IDC_EMP_LIST, &CDBVListTestDlg::OnLvnOdfinditemEmpList)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BTN_SEARCH, &CDBVListTestDlg::OnBnClickedBtnSearch)
    ON_BN_CLICKED(IDC_BTN_DELETE, &CDBVListTestDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

void CDBVListTestDlg::GetDispInfo(LVITEM* pItem)
{
    // called when the list control needs to display data
    if(pItem->mask & LVIF_TEXT)
    {
        // first, move to the appropriate row in the database
        m_DBVListSet.MoveFirst();
        m_DBVListSet.Move(pItem->iItem);

        if(!m_DBVListSet.IsEOF())
        {
#define ASSIGN(text) _tcscpy_s(pItem->pszText, pItem->cchTextMax, text)
            // then display the appropriate column
            switch(pItem->iSubItem)
            {
            case 0: ASSIGN((LPCTSTR)m_DBVListSet.m_Email); break;
            case 1: ASSIGN((LPCTSTR)m_DBVListSet.m_Name); break;
            case 2: ASSIGN((LPCTSTR)m_DBVListSet.m_Phone); break;
            case 3: ASSIGN((LPCTSTR)m_DBVListSet.m_Location); break;
            case 4: ASSIGN((LPCTSTR)m_DBVListSet.m_Title); break;
            case 5: ASSIGN((LPCTSTR)m_DBVListSet.m_Department); break;
            case 6: ASSIGN((LPCTSTR)m_DBVListSet.m_Division); break;
            default: break;
            }
        }
    }
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

    m_ctrlEmpList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT
        | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

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

void CDBVListTestDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    const int MARGIN = 10;
    const int BUTTON_WIDTH = 75;
    const int BUTTON_HEIGHT = 25;

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

    int iButtons[] = {IDOK, IDC_BTN_DELETE, IDC_BTN_SEARCH};
    for (int i = 0; i < ARRAYSIZE(iButtons); ++i) {
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
    m_DBVListSet.SetSort(strFilter);

    m_ctrlEmpList.Invalidate();
    ////
    *pResult = 0;
}


void CDBVListTestDlg::OnLvnGetdispinfoEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
    GetDispInfo(&pDispInfo->item);
    *pResult = 0;
}


void CDBVListTestDlg::OnLvnOdcachehintEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLVCACHEHINT pCacheHint = reinterpret_cast<LPNMLVCACHEHINT>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}


void CDBVListTestDlg::OnLvnOdfinditemEmpList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLVFINDITEM pFindInfo = reinterpret_cast<LPNMLVFINDITEM>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
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


void CDBVListTestDlg::OnBnClickedBtnDelete()
{
    // TODO: Add your control notification handler code here
}
