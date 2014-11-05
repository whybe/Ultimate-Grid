// DAO sorting.h : main header file for the DAO SORTING application
//

#if !defined(AFX_DAOSORTING_H__78794305_9240_11D3_9B43_0020359647BF__INCLUDED_)
#define AFX_DAOSORTING_H__78794305_9240_11D3_9B43_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingApp:
// See DAO sorting.cpp for the implementation of this class
//

class CDAOsortingApp : public CWinApp
{
public:
	CDAOsortingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAOsortingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDAOsortingApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOSORTING_H__78794305_9240_11D3_9B43_0020359647BF__INCLUDED_)
