// Ex30.h : main header file for the EX30 application
//

#if !defined(AFX_EX30_H__0D552879_1D57_11D1_B28B_444553540000__INCLUDED_)
#define AFX_EX30_H__0D552879_1D57_11D1_B28B_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx30App:
// See Ex30.cpp for the implementation of this class
//

class CEx30App : public CWinApp
{
public:
	CEx30App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx30App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx30App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX30_H__0D552879_1D57_11D1_B28B_444553540000__INCLUDED_)
