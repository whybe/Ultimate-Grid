// Ex21.h : main header file for the EX21 application
//

#if !defined(AFX_EX21_H__49810E8A_B43D_11D1_8F89_0020359646CF__INCLUDED_)
#define AFX_EX21_H__49810E8A_B43D_11D1_8F89_0020359646CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx21App:
// See Ex21.cpp for the implementation of this class
//

class CEx21App : public CWinApp
{
public:
	CEx21App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx21App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx21App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX21_H__49810E8A_B43D_11D1_8F89_0020359646CF__INCLUDED_)
