// Ex27View.h : interface of the CEx27View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27VIEW_H__CF04F2AD_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
#define AFX_EX27VIEW_H__CF04F2AD_0EB5_11D1_B1F1_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx27View : public CView
{
protected: // create from serialization only
	CEx27View();
	DECLARE_DYNCREATE(CEx27View)

// Attributes
public:

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

	CEx27Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx27View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex27View.cpp
inline CEx27Doc* CEx27View::GetDocument()
   { return (CEx27Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27VIEW_H__CF04F2AD_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
