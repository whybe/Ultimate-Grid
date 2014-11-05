// SpeedTest.h : main header file for the SPEEDTEST application
//

#if !defined(AFX_SPEEDTEST_H__7686820F_424D_4C59_B8E9_2E78D16640A5__INCLUDED_)
#define AFX_SPEEDTEST_H__7686820F_424D_4C59_B8E9_2E78D16640A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpeedTestApp:
// See SpeedTest.cpp for the implementation of this class
//

class CSpeedTestApp : public CWinApp
{
public:
	CSpeedTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeedTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSpeedTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEEDTEST_H__7686820F_424D_4C59_B8E9_2E78D16640A5__INCLUDED_)
