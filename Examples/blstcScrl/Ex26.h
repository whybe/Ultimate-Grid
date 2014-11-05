// Ex26.h : main header file for the EX26 application
//

#if !defined(AFX_EX26_H__DC52CAD7_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
#define AFX_EX26_H__DC52CAD7_15B2_11D1_A903_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx26App:
// See Ex26.cpp for the implementation of this class
//

class CEx26App : public CWinApp
{
public:
	CEx26App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx26App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26_H__DC52CAD7_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
