// Use UG Lib.h : main header file for the USE UG LIB application
//

#if !defined(AFX_USEUGLIB_H__810886E8_5914_419F_B819_36AA70C47608__INCLUDED_)
#define AFX_USEUGLIB_H__810886E8_5914_419F_B819_36AA70C47608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibApp:
// See Use UG Lib.cpp for the implementation of this class
//

class CUseUGLibApp : public CWinApp
{
public:
	CUseUGLibApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseUGLibApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CUseUGLibApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEUGLIB_H__810886E8_5914_419F_B819_36AA70C47608__INCLUDED_)
