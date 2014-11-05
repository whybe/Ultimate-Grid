// Calendar Demo.h : main header file for the CALENDAR DEMO application
//

#if !defined(AFX_CALENDARDEMO_H__64803C15_6203_4F1F_9785_2A284701588C__INCLUDED_)
#define AFX_CALENDARDEMO_H__64803C15_6203_4F1F_9785_2A284701588C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoApp:
// See Calendar Demo.cpp for the implementation of this class
//

class CCalendarDemoApp : public CWinApp
{
public:
	CCalendarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCalendarDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDEMO_H__64803C15_6203_4F1F_9785_2A284701588C__INCLUDED_)
