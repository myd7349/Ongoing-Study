
// DBVListTest.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDBVListTestApp:
// See DBVListTest.cpp for the implementation of this class
//

class CDBVListTestApp : public CWinApp
{
public:
	CDBVListTestApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDBVListTestApp theApp;