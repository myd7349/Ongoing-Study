// 2013-08-18T23:53+08:00
#pragma once

// CLive555MediaServer command target

#ifdef ENABLE_TERMINATE_LIVE555
#  undef ENABLE_TERMINATE_LIVE555
#endif

class CLive555MediaServer : public CObject
{
public:
	CLive555MediaServer();
	virtual ~CLive555MediaServer();
private:
    CString m_strLive555Path; // path of file live555MediaServer.exe

#ifdef ENABLE_TERMINATE_LIVE555
    HANDLE  m_hLive555Proc;
#endif

public:
    const CString &GetLive555Path() const throw()
    {
        return m_strLive555Path;
    }
    void SetLive555Path(LPCTSTR lpcszPath);
    BOOL Start();
    void Terminate();
};


