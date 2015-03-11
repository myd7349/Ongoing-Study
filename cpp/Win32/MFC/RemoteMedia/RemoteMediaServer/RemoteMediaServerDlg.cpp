
// RemoteMediaServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteMediaServer.h"
#include "RemoteMediaServerDlg.h"
#include "RMSConnect.h"

#include <afxdialogex.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CRemoteMediaServerDlg 对话框

CRemoteMediaServerDlg::CRemoteMediaServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRemoteMediaServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRemoteMediaServerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LST_PLAYLIST, m_ctrlPlaylist);
    DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
    DDX_Control(pDX, IDC_BTN_REMOVE, m_btnRemove);
    DDX_Control(pDX, IDOK, m_btnOK);
    DDX_Control(pDX, IDC_BTN_HELP, m_btnHelp);
}

BEGIN_MESSAGE_MAP(CRemoteMediaServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_ADD, &CRemoteMediaServerDlg::OnBnClickedBtnAdd)
    ON_BN_CLICKED(IDC_BTN_REMOVE, &CRemoteMediaServerDlg::OnBnClickedBtnRemove)
    ON_BN_CLICKED(IDC_BTN_HELP, &CRemoteMediaServerDlg::OnBnClickedBtnHelp)
    ON_WM_DESTROY()
    ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CRemoteMediaServerDlg 消息处理程序

BOOL CRemoteMediaServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    m_ctrlPlaylist.InitUI();
    m_ctrlPlaylist.LoadPlayList();
    InitUI();

    if (m_menuAdd.GetSafeHmenu() == NULL)
    {
        m_menuAdd.LoadMenu(IDM_ADD);
    }

    cmVLPLogDump(RES_STR(IDS_LOG_LIVE555_STARTING));
    if (!m_live555.Start())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_LIVE555_START_FAILED));
        SendMessage(WM_CLOSE);
    }

    cmVLPLogDump(RES_STR(IDS_LOG_SOCKET_INITIALIZING));
    if (!AfxSocketInit())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_SOCKET_INITIALIZING));
        cmVLPLogDumpError();
        SendMessage(WM_CLOSE);
        return TRUE;
    }

    // 创建监听socket
    cmVLPLogDump(RES_STR(IDS_LOG_LISTENING_SOCKET_CREATING));
    DWORD dwPortNum;
    if ((dwPortNum = DEF_PORT_NUM, !m_socketListen.Create(DEF_PORT_NUM))
        && (dwPortNum = REV_PORT_NUM, !m_socketListen.Create(REV_PORT_NUM)))
    {
        cmVLPLogDump(RES_STR(IDS_LOG_LISTENING_SOCKET_CREATE_FAILED));
        cmVLPLogDumpError();
    }
    else
    {
        cmVLPLogDump(RES_STR(IDS_LOG_LISTENING_SOCKET_CREATED), 
            &m_socketListen, dwPortNum);
        m_socketListen.Listen();
    }
    m_socketListen.BoundToUI(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRemoteMediaServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRemoteMediaServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRemoteMediaServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRemoteMediaServerDlg::InitUI()
{
    if (m_icoAdd.Load(IDI_ICO_ADD)) { m_btnAdd.SetIcon(m_icoAdd); }
    else { m_btnAdd.SetWindowText(RES_STR(IDS_ADD)); }

    if (m_icoRemove.Load(IDI_ICO_REMOVE)) { m_btnRemove.SetIcon(m_icoRemove); }
    else { m_btnRemove.SetWindowText(RES_STR(IDS_REMOVE)); }

    if (m_icoHelp.Load(IDI_ICO_HELP)) { m_btnHelp.SetIcon(m_icoHelp); }
    else { m_btnHelp.SetWindowText(RES_STR(IDS_ABOUT)); }

    if (m_icoOK.Load(IDI_ICO_EXIT)) { m_btnOK.SetIcon(m_icoOK); }
    else { m_btnOK.SetWindowText(RES_STR(IDS_EXIT)); }
}

void CRemoteMediaServerDlg::OnBnClickedBtnAdd()
{
#if 0 // TODO 为其他菜单添加消息响应操作
    if (m_menuAdd.GetSafeHmenu() != NULL)
    {
        CRect rtAddBtn;
        m_btnAdd.GetClientRect(&rtAddBtn);
        m_btnAdd.ClientToScreen(&rtAddBtn);
        m_menuAdd.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, 
            rtAddBtn.left, rtAddBtn.bottom, this);
    }
    else
#endif
    {
        SendMessage(WM_COMMAND, MAKEWPARAM(IDM_ADD_FILE, 0));
    }
    m_socketListen.UpdateClientsPlaylist();
}


void CRemoteMediaServerDlg::OnBnClickedBtnRemove()
{
    m_ctrlPlaylist.DeleteSelectedItems();
    m_socketListen.UpdateClientsPlaylist();
}


void CRemoteMediaServerDlg::OnBnClickedBtnHelp()
{
    SendMessage(WM_SYSCOMMAND, MAKEWPARAM(IDM_ABOUTBOX, 0));
}

void CRemoteMediaServerDlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    m_socketListen.Close();
    AfxSocketTerm();
    m_live555.Terminate();
    m_ctrlPlaylist.SaveUILayout();
    m_menuAdd.DestroyMenu();
}

BOOL CRemoteMediaServerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
    if (0 == HIWORD(wParam)) // Menu
    {
        switch (LOWORD(wParam))
        {
        case IDM_ADD_FILE: 
            {
                CFileDialog dlgFile(TRUE, NULL, NULL, 
                    OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST 
                    | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, 
                    RES_STR(IDS_FILETYPEFILTER), this);
                if (dlgFile.DoModal() == IDOK)
                {
                    // Caution:
                    // 如果允许一次选择多个文件，可能由于OPENFILENAME内部
                    // 的存储文件名字的缓冲区不够大而导致无法将所有已选择的文件
                    // 的文件名存储下来
                    CString strReadableSize;
                    POSITION p = dlgFile.GetStartPosition();
                    for (CString strFileName; p != NULL;)
                    {
                        strFileName = dlgFile.GetNextPathName(p);
                        cmGetReadableFileSize(strReadableSize, 
                            cmGetFileSize(strFileName));
                        m_ctrlPlaylist.AddFileToMap(strFileName, strReadableSize);
                    }
                    m_ctrlPlaylist.UpdateContents();
                    m_ctrlPlaylist.SavePlayList();
                }
            }
            break;
        case IDM_ADD_FOLDER: AfxMessageBox(_T("Folder")); break;
        case IDM_ADD_URL: AfxMessageBox(_T("URL")); break;
        default: break;
        }
    }
    return CDialogEx::OnCommand(wParam, lParam);
}

LRESULT CRemoteMediaServerDlg::OnNcHitTest(CPoint point)
{
    LRESULT lRet = CDialogEx::OnNcHitTest(point);
    
    if (HTCLIENT == lRet && ::GetAsyncKeyState(MK_LBUTTON) < 0)
    {
        return HTCAPTION;
    }
    return lRet;
}

CString &CRemoteMediaServerDlg::GetFileGuid(CString &strGuid, const CString &strFileName)
{
    m_ctrlPlaylist.GetFileGUID(strGuid, strFileName);
    return strGuid;
}

const CString &CRemoteMediaServerDlg::GetMediaServerPath() const throw()
{
    return m_live555.GetLive555Path();
}

