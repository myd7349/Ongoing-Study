// RemoteMediaListCtrl.cpp : implementation file
//
#include "stdafx.h"

#ifdef REMOTE_MEDIA_SERVER
#  include "RemoteMediaServer/resource.h"
#elif defined(REMOTE_MEDIA_CLIENT)
#  include "RemoteMediaClient/resource.h"
#else
#  error Definition of REMOTE_MEDIA_SERVER or REMOTE_MEDIA_CLIENT is required. 
#endif

#include "RemoteMediaListCtrl.h"
#include "RemoteMediaUtility.h"

#include <clocale>

// 通过文件名获取对应的Guid
class _CAtrrFindHelper
{
public:
    _CAtrrFindHelper(const CString &strFileName)
    {
        m_strFileName = strFileName;
    }
    bool operator()(pugi::xml_node node) const
    {
        return (::lstrcmpi(m_strFileName, 
            (LPCTSTR)(node.attribute(_T("Name")).as_string())) 
            == 0);
    }
private:
    CString m_strFileName;
};

// CRemoteMediaListCtrl

IMPLEMENT_DYNAMIC(CRemoteMediaListCtrl, CMFCListCtrl)

CRemoteMediaListCtrl::CRemoteMediaListCtrl()
{
    VERIFY(_tsetlocale(LC_ALL, _T("")) != NULL);
}

CRemoteMediaListCtrl::~CRemoteMediaListCtrl()
{
}


void CRemoteMediaListCtrl::AddFileToMap(const CString &strFileName, 
    const CString &strFileSize)
{
    m_mapFiles[strFileName] = strFileSize;
}

void CRemoteMediaListCtrl::DeleteSelectedItems()
{
    ASSERT(GetSafeHwnd() != NULL);
    if (GetSafeHwnd() == NULL)
    {
        return;
    }

    if (GetFirstSelectedItemPosition() == NULL)
    {
        return;
    }

    TRY 
    {
        for (int i = -1; (i = GetNextItem(i, LVNI_SELECTED))
            != -1;)
        {
            m_mapFiles.RemoveKey(GetItemText(i, 0));
        }
    }
    CATCH_ALL (e) 
    {
    }
    END_CATCH_ALL

    UpdateContents();
    SavePlayList();
}

void CRemoteMediaListCtrl::UpdateContents()
{
    ASSERT(GetSafeHwnd() != NULL);
    if (GetSafeHwnd() == NULL)
    {
        return;
    }

    CWaitCursor waitCur;

    DeleteAllItems();

    POSITION p = m_mapFiles.GetStartPosition();
    CString strKey;
    CString strVal;
    for (; p != NULL;)
    {
        m_mapFiles.GetNextAssoc(p, strKey, strVal);
        InsertItem(0, strKey);
    }

    TRY
    {
        int iItemCnt = GetItemCount();
        CString strFileSize;
        for (int i = 0; i < iItemCnt; ++i)
        {
            m_mapFiles.Lookup(GetItemText(i, 0), strFileSize);
            SetItemText(i, 1, strFileSize);
        }
    }
    CATCH_ALL(e)
    {
    }
    END_CATCH_ALL

    Sort(GetSortedColumn(), IsAscending());
}

CString &CRemoteMediaListCtrl::GetFileGUID(CString &strGUID, 
    const CString &strFileName)
{
    strGUID.Empty();

    _CAtrrFindHelper attrFindHelper(strFileName);

    pugi::xml_document xmlPlaylist;
    pugi::xml_parse_result parseRet = 
        xmlPlaylist.load_file(DEFAULT_PLAYLIST_FILENAME);
    if (parseRet)
    {
        pugi::xml_node nodeParent = xmlPlaylist.child(_T("RemoteMediaPlaylist"));
        if (nodeParent)
        {
            pugi::xml_node nodeFind = nodeParent.find_child(attrFindHelper);
            if (nodeFind)
            {
                pugi::xml_attribute attrFileName = nodeFind.attribute(_T("Guid"));
                if (attrFileName)
                {
                    strGUID = (LPCTSTR)attrFileName.as_string();
                }
            }
        }
    }

    return strGUID;
}

void CRemoteMediaListCtrl::InitUI()
{
    ASSERT(GetSafeHwnd() != NULL);
    if (GetSafeHwnd() == NULL)
    {
        return;
    }

    SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    DWORD dwFileNameColWid = AfxGetApp()->GetProfileInt(_T("UIPreference"), 
        _T("FileNameColumnWidth"), 400);
    CRect rtHeaderCtrl;
    GetHeaderCtrl().GetClientRect(&rtHeaderCtrl);
    DWORD dwHeaderCtrlWid = rtHeaderCtrl.Width();
    if (dwFileNameColWid == 0 || dwFileNameColWid > dwHeaderCtrlWid)
    {
        dwFileNameColWid = dwHeaderCtrlWid >> 1;
    }
    InsertColumn(0, RES_STR(IDS_FILENAME), LVCFMT_LEFT, dwFileNameColWid);
    InsertColumn(1, RES_STR(IDS_FILESIZE), LVCFMT_LEFT, 
        AfxGetApp()->GetProfileInt(_T("UIPreference"), 
        _T("FileSizeColumnWidth"), dwHeaderCtrlWid - dwFileNameColWid));
    // TODO 如果第一列宽度是400 第二列宽度是300 而header control的宽度是600的话
    // 即使400、300这两个值已存入注册表，再次启动程序时，水平滚动条也不会自动出现。
    // （这个问题在Win7 64位上会出现，在WinXP 32位上未出现）
    // 而且，在WinXP 32位上使用CDialogEx作为基类，有时候窗体标题栏的颜色不能反映
    // 当前窗体是否激活

    m_iSortedColumn = AfxGetApp()->GetProfileInt(_T("UIPreference"), 
        _T("SortedColumn"), 0);
    m_bAscending = (BOOL)(AfxGetApp()->GetProfileInt(_T("UIPreference"), 
        _T("IsAscending"), TRUE));
}

void CRemoteMediaListCtrl::SaveUILayout()
{
    ASSERT(GetSafeHwnd() != NULL);
    if (GetSafeHwnd() == NULL)
    {
        return;
    }

    AfxGetApp()->WriteProfileInt(_T("UIPreference"), _T("FileNameColumnWidth"), 
        GetColumnWidth(0));
    AfxGetApp()->WriteProfileInt(_T("UIPreference"), _T("FileSizeColumnWidth"), 
        GetColumnWidth(1));
    AfxGetApp()->WriteProfileInt(_T("UIPreference"), _T("SortedColumn"), 
        m_iSortedColumn);
    AfxGetApp()->WriteProfileInt(_T("UIPreference"), _T("IsAscending"), 
        (int)m_bAscending);
}

BOOL CRemoteMediaListCtrl::LoadPlayList(/* LPCTSTR lpcszPlaylist */)
{
    m_mapFiles.RemoveAll();

    pugi::xml_document xmlPlaylist;
    // pugi::xml_parse_result parseRet = xmlPlaylist.load_file(lpcszPlaylist);
    pugi::xml_parse_result parseRet = 
        xmlPlaylist.load_file(DEFAULT_PLAYLIST_FILENAME);
    if (!parseRet)
    {
        return FALSE;
    }

    pugi::xml_node nodeParent = xmlPlaylist.child(_T("RemoteMediaPlaylist"));
    if (!nodeParent)
    {
        return FALSE;
    }

    for (pugi::xml_node_iterator nit = nodeParent.begin(); 
        nit != nodeParent.end(); ++nit)
    {
        pugi::xml_attribute attrFile = nit->attribute(_T("Name"));
        pugi::xml_attribute attrSize = nit->attribute(_T("Size"));

        if (attrFile && attrSize)
        {
            m_mapFiles[attrFile.value()] = attrSize.value();
        }
    }

    UpdateContents();
    return TRUE;
}

BOOL CRemoteMediaListCtrl::SavePlayList(/* LPCTSTR lpcszPlaylist */)
{
    CString strFormat(MAKEINTRESOURCE(IDS_PLSCOMMENT));
    CString strComment;
    CString strDateTime;
    strComment.Format(LPCTSTR(strFormat), cmGetCurDateTime(strDateTime));

    pugi::xml_document xmlPlaylist;
    pugi::xml_node     nodeComment;

    // 写入注释信息
    nodeComment = xmlPlaylist.append_child(pugi::node_comment);
    nodeComment.set_value(reinterpret_cast<const pugi::char_t *>(
        LPCTSTR(strComment)));
    
    // 添加顶层元素
    pugi::xml_node nodeParent = xmlPlaylist.append_child(_T("RemoteMediaPlaylist"));
    if (!nodeParent)
    {
        return FALSE;
    }

    // 添加项
    // TODO: 这种迭代方式和UpdateContents中用到的迭代方式效率上有差异吗？
    // CMap::InitHashTable怎么用？
    CString strGUID;

    for (cmRMPlaylist::CPair *pElem = m_mapFiles.PGetFirstAssoc(); 
        pElem != NULL; pElem = m_mapFiles.PGetNextAssoc(pElem))
    {
        pugi::xml_node nodeItem = nodeParent.append_child(_T("File"));
        if (nodeItem)
        {
            nodeItem.append_attribute(_T("Name")) = pElem->key;
            nodeItem.append_attribute(_T("Size")) = pElem->value;
            nodeItem.append_attribute(_T("Guid")) = cmGenerateGUID(strGUID);
        }
    }

    // 写入XML文件
    // return (BOOL)(xmlPlaylist.save_file(lpcszPlaylist) != false);
    return (BOOL)(xmlPlaylist.save_file(DEFAULT_PLAYLIST_FILENAME) != false);
}

BEGIN_MESSAGE_MAP(CRemoteMediaListCtrl, CMFCListCtrl)
END_MESSAGE_MAP()

void CRemoteMediaListCtrl::Sort(int iColumn, BOOL bAscending, BOOL bAdd)
{
    int iItemCnt = GetItemCount();
    for (int i = 0; i < iItemCnt; ++i)
    {
        SetItemData(i, i);
    }
    CMFCListCtrl::Sort(iColumn, bAscending, bAdd);
}

// MFC上这样描述这个虚函数：
// The framework calls this method when it compares two items. 
// The default implementation always returns 0. 
// You must override this function to provide a sorting algorithm. 
// 完成排序的过程：
// OnColumnClick->Sort->SortItems->CompareProc（一个回调函数）->OnCompareItems
// 想要自定义排序策略，只override这个方法还不行。
// 对list view的各个item排序时通过向list view发送LVM_SORTITEMS消息来实现的
// （实际上，SortItems方法就是做这个事情的）。
// 而MSDN对LVITEM Structure的lParam有这样的描述：
// Value specific to the item. If you use the LVM_SORTITEMS message, 
// the list-view control passes this value to the application-defined 
// comparison function. You can also use the LVM_FINDITEM message to 
// search a list-view control for an item with a specified lParam value. 
// 在MFC里，我们可以通过调用SetItemData方法来设置这个lParam。
// 在哪里调用SetItemData就比较自由了，比如，我们可以override一下
// Sort方法，并在其中SetItemData。
// 这里不得不吐槽一下MFC了：
// 就本程序而言，本程序中的list view control有两列，一列表示文件名，
// 另一列表示文件大小。对文件名这一列进行排序时，我使用普通的字符串比较函数就行了。
// 但是对于文件大小，由于我使用的是诸如：8M、1.0G、300KB这样的readable形式，
// 所以按文件大小进行排序时，我必须重新定义CompareProc函数。这样问题就来了。
// 很显然，既然CRemoteMediaListCtrl如此特化（特化到每一列的排序策略都很具体），
// 那我何不把InsertColumn、InsertItem这些操作都封装到CRemoteMediaListCtrl类中呢？
// 遗憾的是，不太可能。由于MFC中所谓的“二段构造”，即使我们有了一个
// CRemoteMediaListCtrl类型的object，我们也无法保证它已绑定到一个list view control
// 上了，在其上调用Insert*更无从谈起。因而，诸如InsertColumn此类的操作，我没办法
// 把它封装到CRemoteMediaListCtrl中。就本程序而言，我是在CRemoteMediaServerDlg
// 中完成InsertColumn、InsertItem这些操作的。
// 又如，在CRemoteMediaServerDlg::InitDialog中我使用如下语句：
// m_ctrlPlaylist.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
// 来设置list view control的风格，而把这个操作封装到CRemoteMediaListCtrl类的内部也
// 困难。MFC中的“二段构造”带来的问题就是，即使在做一件简单的事情之前，
// 你也不得不考虑一些很难控制的“前提”。比如，如果我想调用
// CListCtrl::SetExtendedStyle时，除了一个CListCtrl类型的对象外，我还得考虑它是否
// 绑定到了一个有效的list view control上（通过Create动态创建也好，或者通过
// add variable使其和对话框资源模板上一个现有的list view control关联一下也好）。
// 这实在是不爽！
// 即使是封装了（正如我已经在CRemoteMediaListCtrl中做的那样），效果也差强人意，更别提
// 封装后的类的复用性。
//
// 2014-07-18 
// 请在MSDN中搜索ON_NOTIFY并阅读：
// TN062: Message Reflection for Windows Controls 
int CRemoteMediaListCtrl::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
    switch (iColumn)
    {
    case 0: 
        return _tcscoll(GetItemText(lParam1, iColumn), 
            GetItemText(lParam2, iColumn));
    case 1:
        return cmCompareReadableFileSize(GetItemText(lParam1, iColumn), 
            GetItemText(lParam2, iColumn));
    default: 
        return CMFCListCtrl::OnCompareItems(lParam1, lParam2, iColumn);
    }
}

