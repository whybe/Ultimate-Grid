// Features.h : main header file for the FEATURES application
//

#if !defined(AFX_FEATURES_H__737DCA55_B2AE_11D1_BF3F_0020359647BF__INCLUDED_)
#define AFX_FEATURES_H__737DCA55_B2AE_11D1_BF3F_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFeaturesApp:
// See Features.cpp for the implementation of this class
//

class CFeaturesApp : public CWinApp
{
public:
	CFeaturesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeaturesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFeaturesApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEATURES_H__737DCA55_B2AE_11D1_BF3F_0020359647BF__INCLUDED_)
