// Use UG DLL.h : main header file for the USE UG DLL application
//

#if !defined(AFX_USEUGDLL_H__5BED8DDC_E84D_4146_8730_E9C5844B6BB6__INCLUDED_)
#define AFX_USEUGDLL_H__5BED8DDC_E84D_4146_8730_E9C5844B6BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUseUGDLLApp:
// See Use UG DLL.cpp for the implementation of this class
//

class CUseUGDLLApp : public CWinApp
{
public:
	CUseUGDLLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseUGDLLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CUseUGDLLApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEUGDLL_H__5BED8DDC_E84D_4146_8730_E9C5844B6BB6__INCLUDED_)
