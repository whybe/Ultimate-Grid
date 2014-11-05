#if !defined(AFX_ADJUST_H__391E9709_157A_11D1_A902_0080C85A0F46__INCLUDED_)
#define AFX_ADJUST_H__391E9709_157A_11D1_A902_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Adjust.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdjuster dialog

class CAdjuster : public CDialog
{
// Construction
public:
	CAdjuster(int colwidth, int rowheight, int sidewidth, int topheight, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdjuster)
	enum { IDD = IDD_COL_ROW_ADJ };
	int		m_rowheight;
	int		m_colwidth;
	int		m_sidewidth;
	int		m_topheight;
	//}}AFX_DATA

// Accessors	
	int GetRowHeight()
		{ return m_rowheight; }
	int GetColWidth()
		{ return m_colwidth; }
	int GetTopHeight()
		{ return m_topheight; }
	int GetSideWidth()
		{ return m_sidewidth; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdjuster)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdjuster)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADJUST_H__391E9709_157A_11D1_A902_0080C85A0F46__INCLUDED_)
