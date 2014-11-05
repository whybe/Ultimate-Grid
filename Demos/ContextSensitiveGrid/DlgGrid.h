#if !defined(AFX_DLGGRID_H__4EDFAB23_FB78_11D3_9835_0020359647BF__INCLUDED_)
#define AFX_DLGGRID_H__4EDFAB23_FB78_11D3_9835_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid dialog
#include "MyCug.h"

class CDlgGrid : public CDialog
{
// Construction
public:
	CDlgGrid(CWnd* pParent = NULL);   // standard constructor

	MyCug m_grid;

// Dialog Data
	//{{AFX_DATA(CDlgGrid)
	enum { IDD = IDD_DLG_GRID };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGrid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGrid)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGRID_H__4EDFAB23_FB78_11D3_9835_0020359647BF__INCLUDED_)
