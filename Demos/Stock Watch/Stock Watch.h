// Stock Watch.h : main header file for the STOCK WATCH application
//

#if !defined(AFX_STOCKWATCH_H__64899012_0FE5_4F1B_92AC_F36032EF003E__INCLUDED_)
#define AFX_STOCKWATCH_H__64899012_0FE5_4F1B_92AC_F36032EF003E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStockWatchApp:
// See Stock Watch.cpp for the implementation of this class
//

class CStockWatchApp : public CWinApp
{
public:
	CStockWatchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockWatchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CStockWatchApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKWATCH_H__64899012_0FE5_4F1B_92AC_F36032EF003E__INCLUDED_)
