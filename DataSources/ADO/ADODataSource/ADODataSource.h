// ADODataSource.h : main header file for the ADODATASOURCE application
//

#if !defined(AFX_ADODATASOURCE_H__7CB3A5C2_D265_4847_AC31_3E078229877C__INCLUDED_)
#define AFX_ADODATASOURCE_H__7CB3A5C2_D265_4847_AC31_3E078229877C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceApp:
// See ADODataSource.cpp for the implementation of this class
//

class CADODataSourceApp : public CWinApp
{
public:
	CADODataSourceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADODataSourceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CADODataSourceApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADODATASOURCE_H__7CB3A5C2_D265_4847_AC31_3E078229877C__INCLUDED_)
