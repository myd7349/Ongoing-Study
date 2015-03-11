/***************************************************************
 * Name:      RemoteMediaUtility.h
 * Purpose:   
 * Author:    myd7349 (myd7349@gmail.com)
 * Created:   2013-08-20 17:45
 * Copyright: 
 * License:   
 **************************************************************/

#pragma once

#ifdef REMOTE_MEDIA_SERVER
#  define DEFAULT_PLAYLIST_FILENAME _T("RMSPlaylist.xml")
#elif defined(REMOTE_MEDIA_CLIENT)
#  define DEFAULT_PLAYLIST_FILENAME _T("RMCPlaylist.xml")
#else
#  error Definition of REMOTE_MEDIA_SERVER or REMOTE_MEDIA_CLIENT is required. 
#endif

typedef CMap<CString, LPCTSTR, CString, LPCTSTR> cmRMPlaylist;

class CRemoteMediaListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CRemoteMediaListCtrl)

public:
	CRemoteMediaListCtrl();
	virtual ~CRemoteMediaListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
private:
    cmRMPlaylist m_mapFiles;
public:
    void AddFileToMap(const CString &strFileName, const CString &strFileSize);
    const int &GetSortedColumn() const throw() { return m_iSortedColumn; }
    const BOOL &IsAscending() const throw() { return m_bAscending; }
    void UpdateContents();
    CString &GetFileGUID(CString &strGUID, const CString &strFileName);
    void DeleteSelectedItems();
    void InitUI();
    void SaveUILayout();
    BOOL LoadPlayList(/* LPCTSTR lpcszPlaylist = DEFAULT_PLAYLIST_FILENAME */);
    BOOL SavePlayList(/* LPCTSTR lpcszPlaylist = DEFAULT_PLAYLIST_FILENAME */);
public:
    void Sort(int iColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE);
    int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);
};
