#pragma once

// CMPlayerWrapper command target

class CMPlayerWrapper : public CObject
{
public:
	CMPlayerWrapper();
	virtual ~CMPlayerWrapper();
    BOOL Preview(const CString &strRTSP);
private:
    CString m_strMPlayer;
};


