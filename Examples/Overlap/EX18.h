// EX18.h : main header file for the EX18 application
//

#if !defined(AFX_EX18_H__B91C6C17_1405_11D1_A901_0080C85A0F46__INCLUDED_)
#define AFX_EX18_H__B91C6C17_1405_11D1_A901_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEX18App:
// See EX18.cpp for the implementation of this class
//

class CEX18App : public CWinApp
{
public:
	CEX18App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEX18App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEX18App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX18_H__B91C6C17_1405_11D1_A901_0080C85A0F46__INCLUDED_)
