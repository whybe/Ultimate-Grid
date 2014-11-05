// MyAccess.h : main header file for the MYACCESS application
//

#if !defined(AFX_MYACCESS_H__6E6BFE77_5152_11D1_B265_002035964AAA__INCLUDED_)
#define AFX_MYACCESS_H__6E6BFE77_5152_11D1_B265_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyAccessApp:
// See MyAccess.cpp for the implementation of this class
//

class CMyAccessApp : public CWinApp
{
public:
	CMyAccessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAccessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyAccessApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYACCESS_H__6E6BFE77_5152_11D1_B265_002035964AAA__INCLUDED_)
