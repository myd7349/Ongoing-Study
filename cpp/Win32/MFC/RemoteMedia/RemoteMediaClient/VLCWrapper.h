// 2013-08-21T11:46+08:00
#pragma once

// CVLCWrapper command target

class CVLCWrapper : public CObject
{
public:
	CVLCWrapper();
	virtual ~CVLCWrapper();
    BOOL IsVLCReady() const;
    BOOL Preview(const CString &strRTSP);
private:
    CString m_strVLCPlayer;
};


