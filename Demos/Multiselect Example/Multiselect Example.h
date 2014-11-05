// Multiselect Example.h : main header file for the MULTISELECT EXAMPLE application
//

#if !defined(AFX_MULTISELECTEXAMPLE_H__9E952215_D32B_11D2_83E4_0020359647BF__INCLUDED_)
#define AFX_MULTISELECTEXAMPLE_H__9E952215_D32B_11D2_83E4_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleApp:
// See Multiselect Example.cpp for the implementation of this class
//

class CMultiselectExampleApp : public CWinApp
{
public:
	CMultiselectExampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiselectExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMultiselectExampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTISELECTEXAMPLE_H__9E952215_D32B_11D2_83E4_0020359647BF__INCLUDED_)
