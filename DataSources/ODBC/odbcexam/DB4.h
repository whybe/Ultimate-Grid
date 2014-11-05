// DB4.h : main header file for the DB4 application
//

#if !defined(AFX_DB4_H__D8C150C7_22E8_11D1_B210_002035964AAA__INCLUDED_)
#define AFX_DB4_H__D8C150C7_22E8_11D1_B210_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDB4App:
// See DB4.cpp for the implementation of this class
//

class CDB4App : public CWinApp
{
public:
	CDB4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDB4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDB4App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB4_H__D8C150C7_22E8_11D1_B210_002035964AAA__INCLUDED_)
