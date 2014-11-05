// db7.h : main header file for the DB7 application
//

#if !defined(AFX_DB7_H__B20EBE89_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
#define AFX_DB7_H__B20EBE89_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ConnectDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDb7App:
// See db7.cpp for the implementation of this class
//

class CDb7App : public CWinApp
{
public:
	CString		m_strSql;		
	CString		m_strDsn;

	CStringArray  m_arrStrDsn;		// read from registry

	CConnectDlg	  m_connDlg;

	CDb7App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDb7App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDb7App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB7_H__B20EBE89_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
