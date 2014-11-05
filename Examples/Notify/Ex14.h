// Ex14.h : main header file for the EX14 application
//

#if !defined(AFX_EX14_H__1E2EF4E7_1504_11D1_A901_0080C85A0F46__INCLUDED_)
#define AFX_EX14_H__1E2EF4E7_1504_11D1_A901_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx14App:
// See Ex14.cpp for the implementation of this class
//

class CEx14App : public CWinApp
{
public:
	CEx14App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx14App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14_H__1E2EF4E7_1504_11D1_A901_0080C85A0F46__INCLUDED_)
