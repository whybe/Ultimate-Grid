// Excel Demo.h : main header file for the EXCEL DEMO application
//

#if !defined(AFX_EXCELDEMO_H__B0329CA8_AC0A_48D0_A600_216DA223C301__INCLUDED_)
#define AFX_EXCELDEMO_H__B0329CA8_AC0A_48D0_A600_216DA223C301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoApp:
// See Excel Demo.cpp for the implementation of this class
//

class CExcelDemoApp : public CWinApp
{
public:
	CExcelDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExcelDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELDEMO_H__B0329CA8_AC0A_48D0_A600_216DA223C301__INCLUDED_)
