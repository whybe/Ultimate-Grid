#if !defined(AFX_PPAGE2_H__4BC5D7D4_B853_11D1_8F92_0020359646CF__INCLUDED_)
#define AFX_PPAGE2_H__4BC5D7D4_B853_11D1_8F92_0020359646CF__INCLUDED_

#include "Mycug-2.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPage2 dialog

class CPPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPage2)

// Construction
public:
	CPPage2();
	~CPPage2();

// Dialog Data
	//{{AFX_DATA(CPPage2)
	enum { IDD = IDD_PPAGE2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_font;
	MyCug2 m_ctrl;
	// Generated message map functions
	//{{AFX_MSG(CPPage2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGE2_H__4BC5D7D4_B853_11D1_8F92_0020359646CF__INCLUDED_)
