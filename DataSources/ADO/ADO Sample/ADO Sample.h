// ADO Sample.h : main header file for the ADO SAMPLE application
//

#if !defined(AFX_ADOSAMPLE_H__8D177357_E78E_449F_B5FB_2C55A68C2447__INCLUDED_)
#define AFX_ADOSAMPLE_H__8D177357_E78E_449F_B5FB_2C55A68C2447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CADOSampleApp:
// See ADO Sample.cpp for the implementation of this class
//

class CADOSampleApp : public CWinApp
{
public:
	CADOSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADOSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CADOSampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADOSAMPLE_H__8D177357_E78E_449F_B5FB_2C55A68C2447__INCLUDED_)
