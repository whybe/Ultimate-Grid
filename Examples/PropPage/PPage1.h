#if !defined(AFX_PPAGE1_H__4BC5D7D3_B853_11D1_8F92_0020359646CF__INCLUDED_)
#define AFX_PPAGE1_H__4BC5D7D3_B853_11D1_8F92_0020359646CF__INCLUDED_

#include "Mycug-1.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPage1 dialog

class CPPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPage1)

// Construction
public:
	CPPage1();
	~CPPage1();

// Dialog Data
	//{{AFX_DATA(CPPage1)
	enum { IDD = IDD_PPAGE1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_font;
	MyCug1 m_ctrl;
	// Generated message map functions
	//{{AFX_MSG(CPPage1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGE1_H__4BC5D7D3_B853_11D1_8F92_0020359646CF__INCLUDED_)
