// EditingDemo.h : main header file for the EDITINGDEMO application
//

#if !defined(AFX_EDITINGDEMO_H__F7282248_116A_4106_88A2_A64B56FF65BB__INCLUDED_)
#define AFX_EDITINGDEMO_H__F7282248_116A_4106_88A2_A64B56FF65BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEditingDemoApp:
// See EditingDemo.cpp for the implementation of this class
//

class CEditingDemoApp : public CWinApp
{
public:
	CEditingDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditingDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEditingDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITINGDEMO_H__F7282248_116A_4106_88A2_A64B56FF65BB__INCLUDED_)
