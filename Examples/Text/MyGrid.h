#if !defined(AFX_MYGRID_H__C13D3613_013D_11D2_88AA_0080C859A484__INCLUDED_)
#define AFX_MYGRID_H__C13D3613_013D_11D2_88AA_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyGrid.h : header file
//

#include "UGCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CMyGrid window

class CMyGrid : public CUGCtrl
{
// Construction
public:
	CMyGrid();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyGrid();

protected:
	virtual void OnSetup();

	CFont m_fontHeading;
	CFont m_fontGrid;
	CFont m_fontCool;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYGRID_H__C13D3613_013D_11D2_88AA_0080C859A484__INCLUDED_)
