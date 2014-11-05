// Ex7.h : main header file for the EX7 application
//

#if !defined(AFX_EX7_H__58B8FCE5_0939_11D1_B1EB_002035964AAA__INCLUDED_)
#define AFX_EX7_H__58B8FCE5_0939_11D1_B1EB_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx7App:
// See Ex7.cpp for the implementation of this class
//

class CEx7App : public CWinApp
{
public:
	CEx7App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx7App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx7App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX7_H__58B8FCE5_0939_11D1_B1EB_002035964AAA__INCLUDED_)
