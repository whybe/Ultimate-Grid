// Ex13View.h : interface of the CEx13View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX13VIEW_H__391E9702_157A_11D1_A902_0080C85A0F46__INCLUDED_)
#define AFX_EX13VIEW_H__391E9702_157A_11D1_A902_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx13View : public CView
{
protected: // create from serialization only
	CEx13View();
	DECLARE_DYNCREATE(CEx13View)

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

// Attributes
public:
	CEx13Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx13View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx13View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx13View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex13View.cpp
inline CEx13Doc* CEx13View::GetDocument()
   { return (CEx13Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX13VIEW_H__391E9702_157A_11D1_A902_0080C85A0F46__INCLUDED_)
