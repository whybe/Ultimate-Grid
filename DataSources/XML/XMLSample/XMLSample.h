// XMLSample.h : main header file for the XMLSAMPLE application
//

#if !defined(AFX_XMLSAMPLE_H__6C1B0AA1_8CDE_46A4_B549_B71F0ED9EB23__INCLUDED_)
#define AFX_XMLSAMPLE_H__6C1B0AA1_8CDE_46A4_B549_B71F0ED9EB23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleApp:
// See XMLSample.cpp for the implementation of this class
//

class CXMLSampleApp : public CWinApp
{
public:
	CXMLSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXMLSampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLSAMPLE_H__6C1B0AA1_8CDE_46A4_B549_B71F0ED9EB23__INCLUDED_)
