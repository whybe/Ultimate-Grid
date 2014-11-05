// RealTime.h : main header file for the REALTIME application
//

#if !defined(AFX_REALTIME_H__622E48E6_C0D2_4EC0_AC09_3527B6B8DD82__INCLUDED_)
#define AFX_REALTIME_H__622E48E6_C0D2_4EC0_AC09_3527B6B8DD82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRealTimeApp:
// See RealTime.cpp for the implementation of this class
//

class CRealTimeApp : public CWinApp
{
public:
	CRealTimeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRealTimeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIME_H__622E48E6_C0D2_4EC0_AC09_3527B6B8DD82__INCLUDED_)
