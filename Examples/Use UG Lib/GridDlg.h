#if !defined(AFX_GRIDDLG_H__9E1428A4_57A9_48D1_BB4A_B5CAF4A7284E__INCLUDED_)
#define AFX_GRIDDLG_H__9E1428A4_57A9_48D1_BB4A_B5CAF4A7284E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridDlg dialog
#include "MyCug.h"

class CGridDlg : public CDialog
{
// Construction
public:
	CGridDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGridDlg)
	enum { IDD = IDD_GRID_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	MyCug m_grid;

	// Generated message map functions
	//{{AFX_MSG(CGridDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDDLG_H__9E1428A4_57A9_48D1_BB4A_B5CAF4A7284E__INCLUDED_)
