// Ex11.h : main header file for the EX11 application
//

#if !defined(AFX_EX11_H__53F2CD45_B505_11D1_BF47_0020359647BF__INCLUDED_)
#define AFX_EX11_H__53F2CD45_B505_11D1_BF47_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx11App:
// See Ex11.cpp for the implementation of this class
//

class CEx11App : public CWinApp
{
public:
	CEx11App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx11App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11_H__53F2CD45_B505_11D1_BF47_0020359647BF__INCLUDED_)
