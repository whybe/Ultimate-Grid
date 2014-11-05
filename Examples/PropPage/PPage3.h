#if !defined(AFX_PPAGE3_H__4BC5D7D5_B853_11D1_8F92_0020359646CF__INCLUDED_)
#define AFX_PPAGE3_H__4BC5D7D5_B853_11D1_8F92_0020359646CF__INCLUDED_

#include "Mycug-3.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPage3 dialog

class CPPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPage3)

// Construction
public:
	CPPage3();
	~CPPage3();

// Dialog Data
	//{{AFX_DATA(CPPage3)
	enum { IDD = IDD_PPAGE3 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	MyCug3 m_ctrl;
	// Generated message map functions
	//{{AFX_MSG(CPPage3)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGE3_H__4BC5D7D5_B853_11D1_8F92_0020359646CF__INCLUDED_)
