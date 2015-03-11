
// RemoteMediaClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteMediaClient.h"
#include "RemoteMediaClientDlg.h"

#include <afxdialogex.h>

#include <cstdlib>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEFAULT_RETRY_TIMES (3)
#define IDT_HANDSHAKE_VERIFY (0x1000)

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


// CRemoteMediaClientDlg 对话框
CRemoteMediaClientDlg::CRemoteMediaClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRemoteMediaClientDlg::IDD, pParent)
    , m_dwRetryTimes(DEFAULT_RETRY_TIMES)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRemoteMediaClientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LST_PLAYLIST, m_ctrlPlaylist);
    DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlServIPAddr);
    DDX_Control(pDX, IDC_BTN_CONNECT, m_btnConn);
    DDX_Control(pDX, IDC_BTN_PREVIEW, m_btnPreview);
    DDX_Control(pDX, IDC_BTN_HELP, m_btnAbout);
    DDX_Control(pDX, IDOK, m_btnExit);
    DDX_Control(pDX, IDC_EDT_PORTNUM, m_edtPortNum);
    DDX_Control(pDX, IDC_CHK_USEDEFPORT, m_chkUseDefPort);
}

BEGIN_MESSAGE_MAP(CRemoteMediaClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BTN_CONNECT, &CRemoteMediaClientDlg::OnBnClickedBtnConnect)
    ON_BN_CLICKED(IDC_BTN_PREVIEW, &CRemoteMediaClientDlg::OnBnClickedBtnPreview)
    ON_BN_CLICKED(IDC_BTN_HELP, &CRemoteMediaClientDlg::OnBnClickedBtnHelp)
    ON_WM_NCHITTEST()
    ON_BN_CLICKED(IDC_CHK_USEDEFPORT, &CRemoteMediaClientDlg::OnBnClickedChkUsedefport)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CRemoteMediaClientDlg 消息处理程序

BOOL CRemoteMediaClientDlg::OnInitDialog()
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
    InitUI();
    LoadSettings();

    cmVLPLogDump(RES_STR(IDS_LOG_SOCKET_INITIALIZING));
    if (!AfxSocketInit())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_SOCKET_INIT_FAILED));
        cmVLPLogDumpError();
        SendMessage(WM_CLOSE);
        return TRUE;
    }
    m_socketConn.BoundToUI(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRemoteMediaClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRemoteMediaClientDlg::OnPaint()
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
HCURSOR CRemoteMediaClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRemoteMediaClientDlg::InitUI()
{
    if (m_icoConn.Load(IDI_ICO_CONN)) { m_btnConn.SetIcon(m_icoConn); }
    else { m_btnConn.SetWindowText(RES_STR(IDS_CONNECT)); }

    m_icoDisConn.Load(IDI_ICO_DISCONN);

    if (m_icoPreview.Load(IDI_ICO_PREVIEW)) { m_btnPreview.SetIcon(m_icoPreview); }
    else { m_btnPreview.SetWindowText(RES_STR(IDS_PREVIEW)); }

    if (m_icoAbout.Load(IDI_ICO_ABOUT)) { m_btnAbout.SetIcon(m_icoAbout); }
    else { m_btnAbout.SetWindowText(RES_STR(IDS_ABOUT)); }

    if (m_icoExit.Load(IDI_ICO_EXIT)) { m_btnExit.SetIcon(m_icoExit); }
    else { m_btnExit.SetWindowText(RES_STR(IDS_EXIT)); }
}

void CRemoteMediaClientDlg::LoadSettings()
{
    m_ctrlServIPAddr.SetAddress(AfxGetApp()->GetProfileInt(
        _T("Settings"), _T("ServerIPAddr"), MAKEIPADDRESS(127, 0, 0, 1)));
    
    CString strPortNum;
    strPortNum.Format(_T("%u"), (DWORD)(AfxGetApp()->GetProfileInt(
        _T("Settings"), _T("TCPPortNum"), DEF_PORT_NUM)));
    m_edtPortNum.SetWindowText(strPortNum);

    m_chkUseDefPort.SetCheck(AfxGetApp()->GetProfileInt(
        _T("Settings"), _T("UseDefPortNum"), BST_CHECKED));
    if (m_chkUseDefPort.GetCheck() == BST_CHECKED)
    {
        m_edtPortNum.EnableWindow(FALSE);
    }
}

void CRemoteMediaClientDlg::SaveSettings()
{
    DWORD dwServIP;
    m_ctrlServIPAddr.GetAddress(dwServIP);
    AfxGetApp()->WriteProfileInt(
        _T("Settings"), _T("ServerIPAddr"), dwServIP);

    CString strPortNum;
    m_edtPortNum.GetWindowText(strPortNum);
    AfxGetApp()->WriteProfileInt(
        _T("Settings"), _T("TCPPortNum"), _tcstoul(strPortNum, NULL, 10));

    AfxGetApp()->WriteProfileInt(
        _T("Settings"), _T("UseDefPortNum"), m_chkUseDefPort.GetCheck());
}

CString &CRemoteMediaClientDlg::RetrieveServIP(CString &strServIP)
{
    DWORD dwServIP;
    if (m_ctrlServIPAddr.GetAddress(dwServIP) != 4)
    {
        strServIP.Empty();
    }
    else
    {
        IN_ADDR sockAddr;
        sockAddr.S_un.S_addr = htonl(dwServIP);
        CA2T szServIP(inet_ntoa(sockAddr));
        strServIP = szServIP;
    }

    return strServIP;
}

void CRemoteMediaClientDlg::ConnectToServer()
{
    if (m_socketConn != INVALID_SOCKET)
    {
        cmVLPLogDump(RES_STR(IDS_LOG_CLOSE_CUR_CONN));
        m_socketConn.Close();
    }

    if (!m_socketConn.Create())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_SOCKET_CREATION_FAILED));
        cmVLPLogDumpError();
        return;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_RETRIEVING_SERVIP));
    RetrieveServIP(m_strServIP);
    if (m_strServIP.IsEmpty())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_RETRIEVED_SERVIP_FAILED));
        return;
    }

    if (m_chkUseDefPort.GetCheck() == BST_CHECKED)
    {
        if (!m_socketConn.Connect(m_strServIP, DEF_PORT_NUM)
            && !m_socketConn.Connect(m_strServIP, REV_PORT_NUM))
        {
            cmVLPLogDump(RES_STR(IDS_LOG_CONNECT_TO_SERV_FAILED));
            m_socketConn.Close();
            return;
        }
    }
    else
    {
        if (m_edtPortNum.GetWindowTextLength() == 0)
        {
            cmVLPLogDump(RES_STR(IDS_LOG_INVALID_PORTNUM));
            return;
        }
        DWORD dwPortNum;
        CString strPortNum;
        m_edtPortNum.GetWindowText(strPortNum);
        dwPortNum = _tcstoul(strPortNum, NULL, 10);

        if (!m_socketConn.Connect(m_strServIP, dwPortNum))
        {
            cmVLPLogDump(RES_STR(IDS_LOG_CONNECT_TO_SERV_FAILED));
            m_socketConn.Close();
            return;
        }
    }
#ifdef _VLPLOG_ON
    CString strServIP;
    UINT uPortNum;
    m_socketConn.GetPeerName(strServIP, uPortNum);
    cmVLPLogDump(RES_STR(IDS_LOG_CONNECTION_ESTABLISHED), 
        &m_socketConn, strServIP, uPortNum);
#endif

    m_btnConn.SetIcon(m_icoDisConn);
    m_ctrlServIPAddr.EnableWindow(FALSE);
    if (m_edtPortNum.IsWindowEnabled())
    {
        m_edtPortNum.EnableWindow(FALSE);
    }
    m_chkUseDefPort.EnableWindow(FALSE);
    // 连接成功后，每隔3s检测服务端是否正确回应客户端（即握手成功）
    SetTimer(IDT_HANDSHAKE_VERIFY, 300, NULL);
}

void CRemoteMediaClientDlg::DisConnectWithServer()
{
    if (m_socketConn != INVALID_SOCKET)
    {
        cmVLPLogDump(RES_STR(IDS_LOG_DISCONN_WITH_SERV));
        ::DeleteFile(DEFAULT_PLAYLIST_FILENAME);
        cmRMDataStreamHeader rmStrmH;
        rmStrmH.rmDatType.rmc_dat_type = cmRM_DATA_T::RMC_CLOSE;
        rmStrmH.dwDatLen = 0;
        m_socketConn.Send(&rmStrmH, sizeof(rmStrmH));
        m_socketConn.Close();
        m_ctrlPlaylist.DeleteAllItems();
        m_btnConn.SetIcon(m_icoConn);
        m_ctrlServIPAddr.EnableWindow(TRUE);
        m_chkUseDefPort.EnableWindow(TRUE);
        m_edtPortNum.EnableWindow(
            m_chkUseDefPort.GetCheck() != BST_CHECKED);
        m_dwRetryTimes = DEFAULT_RETRY_TIMES;
    }
}

void CRemoteMediaClientDlg::TryToHandshake()
{
    if (INVALID_SOCKET == m_socketConn)
    {
        return;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_TRYING_TO_HANDSHAKE), &m_socketConn);
    if (!m_socketConn.IsHandshakeOK())
    {
        if (m_dwRetryTimes > 0)
        {
            cmRMDataStreamHeader rmStrmH;
            rmStrmH.rmDatType.rmc_dat_type = cmRM_DATA_T::RMC_CLIENT;
            rmStrmH.dwDatLen = 0;
            m_socketConn.Send(&rmStrmH, sizeof(rmStrmH));
            --m_dwRetryTimes;
            cmVLPLogDump(RES_STR(IDS_LOG_HANDSHAKE_FAILED), 
                &m_socketConn, m_dwRetryTimes);
        }
        else
        {
            KillTimer(IDT_HANDSHAKE_VERIFY);
            DisConnectWithServer();
        }
    }
    else
    {
        KillTimer(IDT_HANDSHAKE_VERIFY);
        cmVLPLogDump(RES_STR(IDS_LOG_HANDSHAKE_SUCCESS), &m_socketConn);
    }
}

void CRemoteMediaClientDlg::LoadPlaylist()
{
    m_ctrlPlaylist.LoadPlayList();
}

void CRemoteMediaClientDlg::PreviewSelectedFile()
{
    cmVLPLogDump(RES_STR(IDS_LOG_PREPARE_TO_PREVIEW));

    CString strRtspURL = _T("rtsp://");
    CString strFileGuid;
    m_ctrlPlaylist.GetFileGUID(strFileGuid, m_strFileName);
    strRtspURL += m_strServIP + _T("/") + strFileGuid + _T(".mkv");

    cmVLPLogDump(RES_STR(IDS_LOG_RTSP_URL), strRtspURL);
    
    if (!m_vlcPlayer.Preview(strRtspURL))
    {
    }
    else
    {
    }
}

void CRemoteMediaClientDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    DisConnectWithServer();
    AfxSocketTerm();
    SaveSettings();
    m_ctrlPlaylist.SaveUILayout();
}

void CRemoteMediaClientDlg::OnBnClickedBtnConnect()
{
    CWaitCursor waitCur;
    if (INVALID_SOCKET == m_socketConn)
    {  
        ConnectToServer();
    }
    else
    {
        DisConnectWithServer();
    }
}

void CRemoteMediaClientDlg::OnBnClickedBtnPreview()
{
    if (INVALID_SOCKET == m_socketConn)
    {
        return;
    }

    POSITION p = m_ctrlPlaylist.GetFirstSelectedItemPosition();
    if (NULL == p)
    {
        cmVLPLogDump(RES_STR(IDS_LOG_NO_FILE_TO_PREVIEW));
        return;
    }
    
    int iSelItem = m_ctrlPlaylist.GetNextSelectedItem(p);
    m_strFileName = m_ctrlPlaylist.GetItemText(iSelItem, 0);
    if (m_strFileName.IsEmpty())
    {
        cmVLPLogDump(RES_STR(IDS_LOG_GET_FILENAME_FAILED));
        return;
    }

    cmVLPLogDump(RES_STR(IDS_LOG_SEND_RMC_PREVIEW), &m_socketConn);
    cmVLPLogDump(RES_STR(IDS_LOG_NAME_OF_FILE_TO_PREVIEW), m_strFileName);
    // 向服务端发送将要预览的文件的名字
    cmRMDataStreamHeader rmStrmH;
    rmStrmH.rmDatType.rmc_dat_type = cmRM_DATA_T::RMC_PREVIEW;
    rmStrmH.dwDatLen = (m_strFileName.GetLength() + 1) * sizeof(TCHAR);
    m_socketConn.Send(&rmStrmH, sizeof(rmStrmH));
    m_socketConn.Send(LPCTSTR(m_strFileName), rmStrmH.dwDatLen);
}

void CRemoteMediaClientDlg::OnBnClickedBtnHelp()
{
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
}


LRESULT CRemoteMediaClientDlg::OnNcHitTest(CPoint point)
{
    LRESULT lRet = CDialogEx::OnNcHitTest(point);
    
    if (HTCLIENT == lRet && ::GetAsyncKeyState(MK_LBUTTON) < 0)
    {
        return HTCAPTION;
    }
    return lRet;
}

void CRemoteMediaClientDlg::OnBnClickedChkUsedefport()
{
    m_edtPortNum.EnableWindow(
        m_chkUseDefPort.GetCheck() == BST_UNCHECKED);
}

void CRemoteMediaClientDlg::OnTimer(UINT_PTR nIDEvent)
{
    switch (nIDEvent)
    {
    case IDT_HANDSHAKE_VERIFY:
        TryToHandshake();
        break;
    default: break;
    }
    CDialogEx::OnTimer(nIDEvent);
}
