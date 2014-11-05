// Ex26View.h : interface of the CEx26View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26VIEW_H__DC52CADF_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
#define AFX_EX26VIEW_H__DC52CADF_15B2_11D1_A903_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx26View : public CView
{
protected: // create from serialization only
	CEx26View();
	DECLARE_DYNCREATE(CEx26View)

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

// Attributes
public:
	CEx26Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex26View.cpp
inline CEx26Doc* CEx26View::GetDocument()
   { return (CEx26Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26VIEW_H__DC52CADF_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
