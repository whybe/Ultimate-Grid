// Cell Properties.h : main header file for the Cell Properties application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CCellPropertiesApp:
// See Cell Properties.cpp for the implementation of this class
//

class CCellPropertiesApp : public CWinApp
{
public:
	CCellPropertiesApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCellPropertiesApp theApp;