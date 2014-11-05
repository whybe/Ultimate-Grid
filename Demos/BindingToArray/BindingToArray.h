// BindingToArray.h : main header file for the BINDINGTOARRAY application
//

#if !defined(AFX_BINDINGTOARRAY_H__6124CF45_BEEC_4E15_A279_E26977ACB7E6__INCLUDED_)
#define AFX_BINDINGTOARRAY_H__6124CF45_BEEC_4E15_A279_E26977ACB7E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayApp:
// See BindingToArray.cpp for the implementation of this class
//

class CBindingToArrayApp : public CWinApp
{
public:
	CBindingToArrayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBindingToArrayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBindingToArrayApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDINGTOARRAY_H__6124CF45_BEEC_4E15_A279_E26977ACB7E6__INCLUDED_)
