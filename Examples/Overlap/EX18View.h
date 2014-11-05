// EX18View.h : interface of the CEX18View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX18VIEW_H__B91C6C1F_1405_11D1_A901_0080C85A0F46__INCLUDED_)
#define AFX_EX18VIEW_H__B91C6C1F_1405_11D1_A901_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEX18View : public CView
{
protected: // create from serialization only
	CEX18View();
	DECLARE_DYNCREATE(CEX18View)

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;


// Attributes
public:
	CEX18Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEX18View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEX18View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEX18View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EX18View.cpp
inline CEX18Doc* CEX18View::GetDocument()
   { return (CEX18Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX18VIEW_H__B91C6C1F_1405_11D1_A901_0080C85A0F46__INCLUDED_)
