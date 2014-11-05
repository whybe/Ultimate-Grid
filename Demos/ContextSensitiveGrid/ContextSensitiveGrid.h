// ContextSensitiveGrid.h : main header file for the CONTEXTSENSITIVEGRID application
//

#if !defined(AFX_CONTEXTSENSITIVEGRID_H__BC1D8F95_F912_11D3_9831_0020359647BF__INCLUDED_)
#define AFX_CONTEXTSENSITIVEGRID_H__BC1D8F95_F912_11D3_9831_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridApp:
// See ContextSensitiveGrid.cpp for the implementation of this class
//

class CContextSensitiveGridApp : public CWinApp
{
public:
	CContextSensitiveGridApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContextSensitiveGridApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CContextSensitiveGridApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTEXTSENSITIVEGRID_H__BC1D8F95_F912_11D3_9831_0020359647BF__INCLUDED_)
