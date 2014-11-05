// Find and Sort.h : main header file for the FIND AND SORT application
//

#if !defined(AFX_FINDANDSORT_H__9BE51E81_8FB5_4804_978D_60062D721452__INCLUDED_)
#define AFX_FINDANDSORT_H__9BE51E81_8FB5_4804_978D_60062D721452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFindandSortApp:
// See Find and Sort.cpp for the implementation of this class
//

class CFindandSortApp : public CWinApp
{
public:
	CFindandSortApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindandSortApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFindandSortApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDANDSORT_H__9BE51E81_8FB5_4804_978D_60062D721452__INCLUDED_)
