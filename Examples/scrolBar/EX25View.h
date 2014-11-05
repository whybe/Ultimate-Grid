// EX25View.h : interface of the CEX25View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25VIEW_H__391E972B_157A_11D1_A902_0080C85A0F46__INCLUDED_)
#define AFX_EX25VIEW_H__391E972B_157A_11D1_A902_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEX25View : public CView
{
protected: // create from serialization only
	CEX25View();
	DECLARE_DYNCREATE(CEX25View)

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

// Attributes
public:
	CEX25Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEX25View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEX25View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEX25View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthees();
	afx_msg void OnUpdateViewUsexpthees(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EX25View.cpp
inline CEX25Doc* CEX25View::GetDocument()
   { return (CEX25Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25VIEW_H__391E972B_157A_11D1_A902_0080C85A0F46__INCLUDED_)
