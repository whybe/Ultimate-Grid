// Splitter.h : main header file for the SPLITTER application
//

#if !defined(AFX_SPLITTER_H__1D63AE15_0461_11D2_88AF_0080C859A484__INCLUDED_)
#define AFX_SPLITTER_H__1D63AE15_0461_11D2_88AF_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSplitterApp:
// See Splitter.cpp for the implementation of this class
//

class CSplitterApp : public CWinApp
{
public:
	CSplitterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSplitterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTER_H__1D63AE15_0461_11D2_88AF_0080C859A484__INCLUDED_)
