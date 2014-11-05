// Ex30View.h : interface of the CEx30View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX30VIEW_H__0D552881_1D57_11D1_B28B_444553540000__INCLUDED_)
#define AFX_EX30VIEW_H__0D552881_1D57_11D1_B28B_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx30View : public CView
{
protected: // create from serialization only
	CEx30View();
	DECLARE_DYNCREATE(CEx30View)

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

// Attributes
public:
	CEx30Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx30View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx30View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx30View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in Ex30View.cpp
inline CEx30Doc* CEx30View::GetDocument()
   { return (CEx30Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX30VIEW_H__0D552881_1D57_11D1_B28B_444553540000__INCLUDED_)
