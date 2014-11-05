// RTLandLTR.h : main header file for the RTLANDLTR application
//

#if !defined(AFX_RTLANDLTR_H__274B7829_1D2E_47E0_8091_B0905F79CEFE__INCLUDED_)
#define AFX_RTLANDLTR_H__274B7829_1D2E_47E0_8091_B0905F79CEFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRApp:
// See RTLandLTR.cpp for the implementation of this class
//

class CRTLandLTRApp : public CWinApp
{
public:
	CRTLandLTRApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTLandLTRApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRTLandLTRApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTLANDLTR_H__274B7829_1D2E_47E0_8091_B0905F79CEFE__INCLUDED_)
