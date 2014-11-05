// Ex22.h : main header file for the EX22 application
//

#if !defined(AFX_EX22_H__4BC5D7C9_B853_11D1_8F92_0020359646CF__INCLUDED_)
#define AFX_EX22_H__4BC5D7C9_B853_11D1_8F92_0020359646CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx22App:
// See Ex22.cpp for the implementation of this class
//

class CEx22App : public CWinApp
{
public:
	CEx22App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx22App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22_H__4BC5D7C9_B853_11D1_8F92_0020359646CF__INCLUDED_)
